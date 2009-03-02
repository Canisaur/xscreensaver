/* dialogs-Xaw.c --- Athena widgets for demo, options, and password dialogs.
 * xscreensaver, Copyright (c) 1997, 1998 Jamie Zawinski <jwz@jwz.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  No representations are made about the suitability of this
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 *
 * Most of this code contributed by Jon A. Christopher <jac8782@tamu.edu>
 * Copyright 1997, with the same permissions as above.
 */

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <X11/Shell.h>
#include <X11/Xaw/Form.h>
#include <X11/Xaw/Box.h>
#include <X11/Xaw/List.h>
#include <X11/Xaw/Command.h>
#include <X11/Xaw/Toggle.h>
#include <X11/Xaw/Viewport.h>
#include <X11/Xaw/Dialog.h>
#include <X11/Xaw/AsciiText.h>

#include <stdio.h>

#include "visual.h"	/* for visual_depth() */

Widget resources_dialog;
Widget resources_form;
Widget timeout_text;
Widget cycle_text;
Widget fade_text;
Widget ticks_text;
Widget lock_time_text;
Widget passwd_time_text;
Widget verbose_toggle;
Widget cmap_toggle;
Widget fade_toggle;
Widget unfade_toggle;
Widget lock_toggle;
Widget res_done;
Widget res_cancel;

Widget demo_dialog;
Widget demo_form;
Widget label1;
/*Widget label2;*/
/*Widget text_area;*/
Widget demo_list;
Widget text_line;
/*Widget vline;*/
Widget next;
Widget prev;
Widget edit;
Widget done;
Widget restart;
/*Widget spacer;*/

static Widget buttonbox, textbox, okbox;


void
create_resources_dialog(Widget parent, Visual *visual, Colormap colormap)
{
  Widget rlabel;
  int depth = visual_depth(XtScreen(parent), visual);

  resources_dialog = 
    XtVaCreatePopupShell("resources_dialog", transientShellWidgetClass, parent,
			 XtNtitle, NULL,
			 XtNoverrideRedirect, TRUE,
			 XtNvisual, visual,
			 XtNcolormap, colormap,
			 XtNdepth, depth,
			 NULL);

  resources_form =
    XtVaCreateManagedWidget("resources_form", formWidgetClass,
			    resources_dialog,
			 XtNvisual, visual,
			 XtNcolormap, colormap,
			 XtNdepth, depth,
			    NULL);

  rlabel = XtVaCreateManagedWidget("label1", labelWidgetClass, resources_form,
				   XtNleft, XtChainLeft,
				   XtNright, XtChainRight,
				   XtNtop, XtChainTop,
				   NULL);

  textbox=
    XtVaCreateManagedWidget("textbox", formWidgetClass, resources_form,
			    XtNleft, XtChainLeft,
			    XtNfromVert, rlabel,
			    NULL);
  okbox=
    XtVaCreateManagedWidget("textbox", boxWidgetClass, resources_form,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNfromVert, textbox,
			    XtNorientation, XtorientHorizontal,
			    NULL);
  timeout_text=
    XtVaCreateManagedWidget("timeout", dialogWidgetClass, textbox,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNtop, XtChainTop,
			    NULL);
  cycle_text=
    XtVaCreateManagedWidget("cycle", dialogWidgetClass, textbox,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNfromVert, timeout_text,
			    NULL);
  fade_text=
    XtVaCreateManagedWidget("fade", dialogWidgetClass, textbox,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNfromVert, cycle_text,
			    NULL);

  ticks_text =
    XtVaCreateManagedWidget("ticks", dialogWidgetClass, textbox,
			    XtNtop, XtChainTop,
			    XtNright, XtChainRight,
			    XtNfromHoriz, timeout_text,
			    NULL);

  lock_time_text =
    XtVaCreateManagedWidget("lockTime", dialogWidgetClass, textbox,
			    XtNfromVert, ticks_text,
			    XtNright, XtChainRight,
			    XtNfromHoriz, cycle_text,
			    NULL);

  passwd_time_text =
    XtVaCreateManagedWidget("passwdTime", dialogWidgetClass, textbox,
			    XtNfromVert, lock_time_text,
			    XtNright, XtChainRight,
			    XtNfromHoriz, fade_text,
			    NULL);

  buttonbox=
    XtVaCreateManagedWidget("buttonbox", boxWidgetClass, resources_form,
			    XtNfromVert, rlabel,
			    XtNfromHoriz, textbox,
			    XtNright, XtChainRight,
			    XtNorientation, XtorientVertical,
			    NULL);
  verbose_toggle =
    XtVaCreateManagedWidget("verbose", toggleWidgetClass, buttonbox,
			    NULL);
  cmap_toggle =
    XtVaCreateManagedWidget("cmap", toggleWidgetClass, buttonbox,
			    NULL);
  fade_toggle =
    XtVaCreateManagedWidget("fade", toggleWidgetClass, buttonbox,
			    NULL);
  unfade_toggle =
    XtVaCreateManagedWidget("unfade", toggleWidgetClass, buttonbox,
			    NULL);
  lock_toggle = 
    XtVaCreateManagedWidget("lock", toggleWidgetClass, buttonbox,
			    NULL);


  res_done = XtVaCreateManagedWidget("done", commandWidgetClass, okbox,
				     NULL);
  res_cancel = XtVaCreateManagedWidget("cancel", commandWidgetClass, okbox,
				       NULL);
}

void
create_demo_dialog(Widget parent, Visual *visual, Colormap colormap)
{
  Widget subform, box, viewport, label2;
  int depth = visual_depth(XtScreen(parent), visual);

  demo_dialog = 
    XtVaCreatePopupShell("demo_dialog", transientShellWidgetClass, parent,
			 XtNtitle, NULL,
			 XtNoverrideRedirect, TRUE,
			 XtNvisual, visual,
			 XtNcolormap, colormap,
			 XtNdepth, depth,
			 NULL);

  demo_form =
    XtVaCreateManagedWidget("demo_form", formWidgetClass, demo_dialog,
			 XtNvisual, visual,
			 XtNcolormap, colormap,
			 XtNdepth, depth,
			    NULL);

  label1 = XtVaCreateManagedWidget("label1", labelWidgetClass, demo_form,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNtop, XtChainTop,
			    NULL);

  label2 = XtVaCreateManagedWidget("label2", labelWidgetClass, demo_form,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNfromVert, label1,
			    NULL);

  subform =
    XtVaCreateManagedWidget("subform", formWidgetClass, demo_form,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNfromVert, label2,
			    NULL);
  viewport =
    XtVaCreateManagedWidget("viewport", viewportWidgetClass, subform,
			    XtNtop, XtChainTop,
			    XtNleft, XtChainLeft,
			    XtNright, XtChainRight,
			    XtNallowVert, TRUE,
			    XtNallowHoriz, TRUE,
			    XtNforceBars, TRUE,
			    NULL);

  demo_list = XtVaCreateManagedWidget("demo_list", listWidgetClass, viewport,
				      XtNverticalList, TRUE,
				      XtNdefaultColumns, 1,
				      NULL);

  text_line = XtVaCreateManagedWidget("text", asciiTextWidgetClass, subform,
				      XtNleft, XtChainLeft,
				      XtNright, XtChainRight,
				      XtNfromVert, viewport,
				      XtNbottom, XtChainBottom,
				      XtNeditType, XawtextEdit,
				      NULL);

  box =
    XtVaCreateManagedWidget("box", boxWidgetClass, demo_form,
			    XtNleft, XtChainLeft,
			    XtNfromVert, subform,
			    XtNbottom, XtChainBottom,
			    XtNright, XtChainRight,
			    XtNorientation, XtEhorizontal,
			    NULL);
  next = XtVaCreateManagedWidget("next", commandWidgetClass, box, NULL);
  prev = XtVaCreateManagedWidget("prev", commandWidgetClass, box, NULL);
  edit = XtVaCreateManagedWidget("edit", commandWidgetClass, box, NULL);
  restart = XtVaCreateManagedWidget("restart", commandWidgetClass, box, NULL);
  done = XtVaCreateManagedWidget("done", commandWidgetClass, box, NULL);
}