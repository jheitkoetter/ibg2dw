/*
 *  ibg2dw(1) -- Copyright (c) 2016 Joerg Heitkoetter (joke). All rights reserved.
 *
 *  Send bugs, comments, and all the fish to joke@verizon.com
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, 59 Temple Place--Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef lint
static char *rcsid = "$Id: ibg2dw.c,v Mon Mar 14 11:18:59 CET 2016 joke Rel $";
#endif


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

char *program_name = "ibmi2dw";
char *program_version = "1.0";
char *program_uri = "https://github.com/jheitkoetter/ibg2dw.git";

int debug = 0;

void
main (argc, argv)
     int argc;
     char **argv;
{
  FILE *fp;
  int c;

  while ((c = getopt (argc, argv, "vd")) != EOF)
    switch (c)
      {
      case 'd':
	debug++;
	break;

      case 'v':
	note (EXIT_SUCCESS);
	break;

      default:
	usage (EXIT_FAILURE);
	break;
      }

  if (!(argc - optind))		/* nothing left */
    csv2dw (stdin, "<stdin>");
  else
    for (; optind < argc; optind++)
      {
	if ((fp = fopen (argv[optind], "r")) == NULL)
	  {
	    fprintf (stderr, "%s: No such file: %s\n", program_name, argv[optind]);
	    continue;
	  }
	csv2dw (fp, argv[optind]);
	fclose (fp);
      }

  exit (EXIT_SUCCESS);
}

#define CR '\r'
#define LF '\n'

void
csv2dw (fp, file)
     FILE *fp;
     char *file;
{
  int i = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  while ((read = getline(&line, &len, fp)) != -1) {
    i++;
    if (debug) {
      fprintf (stderr, "Retrieved line of length %zu :\n", read);
      fprintf (stderr, "%s", line);
    }
  }
  if (debug)
    fprintf (stderr, "%d lines read\n", i);

  free (line);

  exit (EXIT_SUCCESS);
}

usage (code)
     int code;
{
  fprintf (stderr, "usage: %s [-v]\n", program_name);
  exit (code);
}

note (code)
     int code;
{
  fprintf (stderr, "This is %s, version %s, available at %s\n", program_name, program_version, program_uri);
  fprintf (stderr, "Copyright (c) 2016 Joerg Heitkoetter (joke). All rights reserved.\n");
  fprintf (stderr, "Send comments, bugs, and all the fish to <joke@verizon.com>\n");
  exit (code);
}

