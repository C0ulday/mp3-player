// ----- First page : the splashscreen 
void splashScreen(){
  drawNote();
}

// little music note
void drawNote(int x, int y) {
  u8g2_DrawDisc(&u8g2, x, y + 3, 1, U8G2_DRAW_ALL);
  u8g2_DrawLine(&u8g2, x + 1, y + 3, x + 1, y);
  u8g2_DrawLine(&u8g2, x + 1, y, x + 3, y + 1);
}

// star
void drawStar(int cx, int cy, int size) {

  u8g2_DrawLine(&u8g2,cx, cy - size, cx, cy + size);
  u8g2_DrawLine(&u8g2,cx - size, cy, cx + size, cy);

  int diag = size / 2;

  u8g2_DrawLine(&u8g2,cx - diag, cy - diag, cx + diag, cy + diag);
  u8g2_DrawLine(&u8g2,cx - diag, cy + diag, cx + diag, cy - diag);
}


