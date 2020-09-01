# Pop star
My second C++ project cooperating with other 2 classmates in Nanchang University: 2017.9.14 - 2017.9.20

Pop star is a stand-alone mini game implemented with C++, Qt and MySQL database. Users click a star label next to other labels with the same color to destroy these stars. Three different difficulty modes can be selected and the number of colors in these three modes increases from 4 to 6 accordingly. Game records are stored in local database.

I completed the design of the class, the realization of the game logic, and the transfer of data between windows in the interface feature effects.

## Key technical points
### 1. Special interface effects
> * Background music
> > QSound
> > Double click
> > Timer
> * Jump between windows
> > Signals and slot functions
> * Display a large amount of text read from files in a dialog box
> > QTextStream
> * Change shape of cursor
> > Qcursor
### 2. Game logic
> * Find stars that can be eliminated around the clicked one
> > Breadth first search
> * Move the remaining stars to fill the empty position after eliminating
> > A variant of exchange sorting algorithm
> * Determine whether there are stars continue to be eliminated
> > Breadth first search
> * Calculate scores
> > In one elimination, elimination score = number of eliminated stars ^ 2 * 5
> > When the number of remaining stars is more than 10, 20 points will be deducted for each star beyond the 10, and the deducted points will not exceed the obtained points.
> > When the number of remaining stars is less than 10, add points, and the extra points = (10 - number of remaining stars) * 20
