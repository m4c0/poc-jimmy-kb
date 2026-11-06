#define KB_TEXT_SHAPE_IMPLEMENTATION
#include "kb_text_shape.h"

#define MSG "Olá mundão véi!¡"

int main() {
  kbts_shape_context * ctx = kbts_CreateShapeContext(0, 0);
  if (!kbts_ShapePushFontFromFile(ctx, "unifont-18.0.01.otf", 0)) return 1;

  kbts_ShapeBegin(ctx, KBTS_DIRECTION_DONT_KNOW, KBTS_LANGUAGE_DONT_KNOW);
  kbts_ShapeUtf8(ctx, MSG, sizeof(MSG) - 1, KBTS_USER_ID_GENERATION_MODE_CODEPOINT_INDEX);
  kbts_ShapeEnd(ctx);

  int cx = 0, cy = 0;
  kbts_run run;
  while (kbts_ShapeRun(ctx, &run)) {
    kbts_glyph * glyph;
    while (kbts_GlyphIteratorNext(&run.Glyphs, &glyph)) {
      int gx = cx + glyph->OffsetX;
      int gy = cy + glyph->OffsetY;

      printf("glyph %d @%d,%d\n", glyph->Id, gx, gy);

      cx += glyph->AdvanceX;
      cy += glyph->AdvanceY;
    }
  }
}
