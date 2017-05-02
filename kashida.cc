// Ebrahim Byagowi <ebrahim@gnu.org>
#include <stdio.h>
#include <stdlib.h>

#include <hb.h>
#include <hb-directwrite.h>

int main(int argc, char **argv) {
  if (argc == 1) {
    char* argv2[] = { argv[0], "C:\\Windows\\Fonts\\tahoma.ttf", "10000", "1605", "1578", "1606" };
    argv = argv2;
    argc = 6;
  }

  float width = atof(argv[2]);

  int text_length = argc - 3;
  hb_codepoint_t *text = new hb_codepoint_t[text_length];
  for (int i = 0; i < argc - 3; ++i) {
    text[i] = atoi(argv[i + 3]);
  }

  FILE *font_file = fopen(argv[1], "rb");
  fseek(font_file, 0, SEEK_END);
  long font_file_size = ftell(font_file);
  fseek(font_file, 0, SEEK_SET);
  char *font = (char*)malloc(font_file_size);
  fread(font, font_file_size, 1, font_file);
  fclose(font_file);

  hb_blob_t *hb_blob = hb_blob_create(font, font_file_size, HB_MEMORY_MODE_READONLY, nullptr, nullptr);
  hb_face_t *hb_face = hb_face_create(hb_blob, 0);
  hb_font_t *hb_font = hb_font_create(hb_face);

  unsigned int upem = hb_face_get_upem(hb_face);
  hb_font_set_scale(hb_font, upem, upem);

  hb_buffer_t *hb_buffer = hb_buffer_create();
  hb_buffer_set_direction(hb_buffer, HB_DIRECTION_RTL);
  hb_buffer_set_language(hb_buffer, hb_language_from_string("fa", 2));
  hb_buffer_set_script(hb_buffer, HB_SCRIPT_ARABIC);
  hb_buffer_add_codepoints(hb_buffer, text, text_length, 0, -1);
  hb_directwrite_shape_experimental_width(hb_font, hb_buffer, 0, 0, width);
  
  unsigned int len;
  hb_glyph_info_t *infos;
  hb_glyph_position_t *positions;
  len = hb_buffer_get_length(hb_buffer);
  infos = hb_buffer_get_glyph_infos(hb_buffer, NULL);
  positions = hb_buffer_get_glyph_positions(hb_buffer, NULL);

  for (unsigned int i = 0; i < len; i++) {
    hb_glyph_info_t *info = &infos[i];

    printf("%d,", info->codepoint);
  }

  hb_buffer_clear_contents(hb_buffer);
  hb_buffer_destroy(hb_buffer);
  hb_font_destroy(hb_font);
  hb_face_destroy(hb_face);
  hb_blob_destroy(hb_blob);
  free(font);

  return 0;
}
