# Learning Recommender


"Learning Recommender" je jednostavan program koji nasumicno daje predmete sta vjezbati tokom radnog dana,
u skladu sa vasim mogucnostima! Po defaultu, program daje predmete za vjezbanje tog dana i obicno su to vjezbe koji traju 90 minuta (logika programa je tako napravljena)
Program trazi od vas unos podataka vezano za vas semestar i kurseve tokom sedmice

FILES

"casova.txt" file sluzi za spremanje podataka o sedmicnim casovima pojedinih predmeta

"iskoristeno.txt" je file koji sluzi da spasavanje predmeta koji je program vec predlozio i
iskoristio, te na ovaj nacin bi mogao da kaze koliko ste ulozili vremena u koji predmet

"predmeti.txt" file sluzi za spremanje podataka o nazivima vasih kurseva

"sedmica.txt" file sluzi za spremanje sedmicnih casova u danima od ponedjeljka do subote redom

PROGRAMI

"getPredmete.cpp" je C++ file koji dobavlja podatke od korisnika, te spasava u gore navedenim fileovima

"displayVjezbanje.cpp" je C++ file koji daje prijedloge za vjezbanje za odredjeni dan na osnovu podatak unesenih u "getPredmete.cpp"



UPUTSVO (za pocetak)

Ako prvi put imate ovaj paket, prvo pokrenite getPredmete.cpp za unos podataka o semestru i o vasim predmetima, te koliko casova imate tokom sedmice i po predmetu (sedmicno)
Poslije toga, koristite displayVjezbanje kako bi, pametno i nasumicno, davalo prijedloge sta biste mogli da vjezbate taj dan, u zavisnosti koliki je stres faktor u tom danu.
Stres level u danu je, po defaultu 10 i smanjuje se za broj casova taj dan, te se smanjuje za dva za svaki prijedlog! Ideja je na bazi ECTS kredita!
Tokom sedmice, mozete primijetiti da cete odredjene predmete dobiti onoliko puta predlozeno koliko imate casova tog predmeta sedmicno, te se program vise fokusira da vam predlozi te predmete,
nego predmete na kojem imate manje casova!

U BUDUCNOSTI

Licno, planiram da ovo nadogradim sa GUI (vjerovatno cu da iskoristim Python u te svrhe, zbog licne vjezbe, a mozda budem od ovoga napravio stranicu, vidjet cemo gdje put bude odveo).
