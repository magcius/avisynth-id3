
#include <stdlib.h>
#include <string.h>

#include "avisynth_c.h"
#include "tag_c.h"

static AVSC_CC void
free_strings (void                  *user_data,
              AVS_ScriptEnvironment *env)
{
  taglib_tag_free_strings ();
}

#define METADATA_TYPES \
  STR(title) \
  STR(artist) \
  STR(album) \
  STR(comment) \
  STR(genre) \
  INT(year) \
  INT(track) \
  /* */

#define STR(name) \
static AVS_Value AVSC_CC \
song_##name (AVS_ScriptEnvironment *env, \
             AVS_Value              args, \
             void                  *user_data) \
{ \
	TagLib_File *f = taglib_file_new (avs_as_string (avs_array_elt (args, 0))); \
	AVS_Value v = avs_new_value_string(avs_save_string (env, taglib_tag_##name (taglib_file_tag (f)), -1)); \
	taglib_file_free (f); \
	return v; \
}

#define INT(name) \
static AVS_Value AVSC_CC \
song_##name (AVS_ScriptEnvironment *env, \
             AVS_Value              args, \
             void                  *user_data) \
{ \
	TagLib_File *f = taglib_file_new (avs_as_string (avs_array_elt (args, 0))); \
	AVS_Value v = avs_new_value_int (taglib_tag_##name (taglib_file_tag (f))); \
	taglib_file_free (f); \
	return v; \
}

METADATA_TYPES

#undef STR
#undef INT

const char* AVSC_CC avisynth_c_plugin_init(AVS_ScriptEnvironment* env)
{
#define STR(name) avs_add_function (env, "Song" #name, "s", song_##name, NULL);
#define INT(name) avs_add_function (env, "Song" #name, "i", song_##name, NULL);
METADATA_TYPES
#undef STR
#undef INT

	avs_at_exit (env, free_strings, NULL);
	return "ID3";
}

