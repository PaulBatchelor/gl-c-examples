#include <cairo.h>

int
main (int argc, char *argv[])
{
        cairo_surface_t *surface;
        cairo_t *cr;
	cairo_pattern_t *linpat, *radpat;

        surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, 120, 120);
        cr = cairo_create (surface);
	/* Examples are in 1.0 x 1.0 coordinate space */
	cairo_scale (cr, 120, 120);

	/* Drawing code goes here */
	linpat = cairo_pattern_create_linear (0, 0, 1, 1);
	cairo_pattern_add_color_stop_rgb (linpat, 0, 0, 0.3, 0.8);
	cairo_pattern_add_color_stop_rgb (linpat, 1, 0, 0.8, 0.3);

	radpat = cairo_pattern_create_radial (0.5, 0.5, 0.25, 0.5, 0.5, 0.75);
	cairo_pattern_add_color_stop_rgba (radpat, 0, 0, 0, 0, 1);
	cairo_pattern_add_color_stop_rgba (radpat, 0.5, 0, 0, 0, 0);

	cairo_set_source (cr, linpat);
	cairo_pattern_destroy (linpat);

	cairo_mask (cr, radpat);
	cairo_pattern_destroy (radpat);

	/* Write output and clean up */
        cairo_surface_write_to_png (surface, "mask.png");
        cairo_destroy (cr);
        cairo_surface_destroy (surface);

        return 0;
}
