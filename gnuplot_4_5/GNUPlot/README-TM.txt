Here (in this zip file) you find precompiled 
Windows binaries of the CURRENT DEVELOPMENT VERSION 
of gnuplot as available from gnuplot's SourceForge CVS tree
The binaries are built using a GCC-4.5.2 and are opimized by '-O3' 
option for higher perfomance.

The document gives addtional information to README.Windows.gpteam 
which is officially provided by Gnuplot Team.
(In the official ditrubution, the file name of the document is 'README.Windows'
prepared for gnuplot 4.4.2)

See also files ChangeLog and NEWS for more details on updates and new features.

THIS IS A DEVELOPMENT VERSION OF GNUPLOT. IN ADDITION, IT IS BUILT BY GCC-4.5.2 
WITH -O3 OPTION. USE AT YOUR OWN RISK.

You are welcome to download the sources from
 export CVSROOT=:pserver:anonymous@gnuplot.cvs.sourceforge.net:/cvsroot/gnuplot
 cvs login
 cvs -z3 checkout gnuplot

The latest "official" version of gnuplot is available from the below site, 
  - gnuplot.sourceforge.net

*********
* Notes *
********************************************************************************
From 2010-03-19, the renamed fontconfig utlity 'fc-list-gp.exe' is attached.
Original name of this file 'fc-list.exe'. The reason why I rename this file is
to avoid the possibility of confliction other 'fc-list.exe' files on provided in 
other applications.
(e.g. XeTeX )

In the use of 'fc-list-gp.exe', the current directory is set where gnuplot is 
installed. This ulitilty outputs a list of fonts managed by the fontconfig 
library used in this gnuplot distribution.  The list is coded in the utf-8 format. 
Please use redirection like

gnuplot> !fc-list-gp > fc-list.txt
gnuplot> !notepad fc-list.txt

********************************************************************************
From 2010-03-23, dependency libraries are updated and built myself as possible.
(The GLib, cairo, and Pange are still imported from 
http://www.gtk.org/download-windows.html')

The most important chage is the replacement of libgd.  The previous library has 
bugs.  The most serious bug is related the fontconfig libraries.  Owing to the 
bug, the old syntax of font setting the gd related terminals (png, jpeg, and gif) 
is not allowed.  Only new syntax (syntax for wxt, pngcairo, and pdfcairo), which
is based on the fontconfig technology.  The fix of the bug of libgd allow to use 
the old and new syntax for gd related terminals.

Please refer
http://old.nabble.com/gd-and-fontconfig-td27967801.html

On July 5, a bug from inconsistency between the libjpeg and the libgd is fixed.

Please refer
http://old.nabble.com/-Gnuplot-bugs--JPEG-plot-problem-gnuplot-v4.4.0-td29056054.html
********************************************************************************
On 2010-05-06, I have carried out a trial revise README.Windows.gpteam for 
intall process on Windows Vista and 7.
*********************************************************************************
From 2011-02-26, chm sytle windows help file is attached to the package.  Legacy
style wgnuplot.hlp is no longer distributed.
*******************************************************************************

(Latest ChangeLog date, 2011-09-09)
Tatsuro Matsuoka, September 2011
