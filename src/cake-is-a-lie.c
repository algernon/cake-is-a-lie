#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <caca.h>
#include <Imlib2.h>

#include "config.h"

struct image
{
    char *pixels;
    unsigned int w, h;
    struct caca_dither *dither;
    void *priv;
};

static struct image *
tcial_image_load (const char *filename)
{
  struct image *im = malloc (sizeof (struct image));
  unsigned int depth, bpp, rmask, gmask, bmask, amask;
  Imlib_Image image;

  image = imlib_load_image (filename);

  if (!image)
    {
      free (im);
      return NULL;
    }

  imlib_context_set_image (image);
  im->pixels = (char *)imlib_image_get_data_for_reading_only ();
  im->w = imlib_image_get_width ();
  im->h = imlib_image_get_height ();
  rmask = 0x00ff0000;
  gmask = 0x0000ff00;
  bmask = 0x000000ff;
  amask = 0xff000000;
  bpp = 32;
  depth = 4;

  im->dither = caca_create_dither (bpp, im->w, im->h, depth * im->w,
                                   rmask, gmask, bmask, amask);
  if (!im->dither)
    {
      imlib_free_image ();
      free (im);
      return NULL;
    }

  im->priv = (void *)image;

  return im;
}

static const char *
try_filename_in_dir (const char *dir, const char *fn)
{
  static char filename[4096];

  memset (filename, 0, sizeof(filename));

  strcat (filename, dir);
  strcat (filename, "/");
  strcat (filename, fn);

  return filename;
}


int
main (void)
{
  caca_canvas_t *cv;
  caca_display_t *dp;
  caca_event_t ev;
  int ww, wh, i;
  const char *message = "Happy 20th\nbirthday,\nDebian!";

  struct image *cake, *logo;

  logo = tcial_image_load (try_filename_in_dir (DATADIR, "debian-logo.png"));
  if (!logo)
    logo = tcial_image_load (try_filename_in_dir ("../data", "debian-logo.png"));
  cake = tcial_image_load (try_filename_in_dir (DATADIR, "cake.png"));
  if (!cake)
    cake = tcial_image_load (try_filename_in_dir ("../data", "cake.png"));

  if (!logo || !cake || (access ("/usr/share/figlet/ivrit.flf", R_OK) != 0))
    return 1;

  dp = caca_create_display_with_driver (NULL, "ncurses");
  if (!dp)
    return 1;

  cv = caca_get_canvas (dp);

  caca_set_display_title (dp, message);
  caca_set_color_ansi (cv, CACA_WHITE, CACA_BLACK);

  ww = caca_get_canvas_width (cv);
  wh = caca_get_canvas_height (cv);

  caca_dither_bitmap (cv, ww / 2, 0, ww / 2, wh / 2, logo->dither, logo->pixels);
  caca_refresh_display (dp);

  caca_get_event (dp, CACA_EVENT_KEY_PRESS, &ev, -1);

  caca_dither_bitmap (cv, ww / 2, wh / 2, ww / 2, wh / 2, cake->dither, cake->pixels);
  caca_refresh_display (dp);

  caca_get_event (dp, CACA_EVENT_KEY_PRESS, &ev, -1);

  caca_dither_bitmap (cv, ww / 2, 0, ww / 2, wh / 2, logo->dither, logo->pixels);

  caca_canvas_set_figfont (cv, strdup ("/usr/share/figlet/ivrit.flf"));

  for (i = 0; i < strlen (message); i++)
    caca_put_figchar (cv, message[i]);

  caca_refresh_display (dp);
  caca_get_event (dp, CACA_EVENT_KEY_PRESS, &ev, -1);
  caca_free_display (dp);

  return 0;
}
