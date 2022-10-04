
CREATE TABLE DEPARTAMENTS
         (	NUM_DPT INTEGER,
	NOM_DPT CHAR(20),
	PLANTA INTEGER,
	EDIFICI CHAR(30),
	CIUTAT_DPT CHAR(20),
	PRIMARY KEY (NUM_DPT));

CREATE TABLE PROJECTES
         (	NUM_PROJ INTEGER,
	NOM_PROJ CHAR(10),
	PRODUCTE CHAR(20),
	PRESSUPOST INTEGER,
	PRIMARY KEY (NUM_PROJ));

CREATE TABLE EMPLEATS
         (	NUM_EMPL INTEGER,
	NOM_EMPL CHAR(30),
	SOU INTEGER,
	CIUTAT_EMPL CHAR(20),
	NUM_DPT INTEGER,
	NUM_PROJ INTEGER,
	PRIMARY KEY (NUM_EMPL),
	FOREIGN KEY (NUM_DPT) REFERENCES DEPARTAMENTS (NUM_DPT),
	FOREIGN KEY (NUM_PROJ) REFERENCES PROJECTES (NUM_PROJ));

INSERT INTO  DEPARTAMENTS VALUES (5,'VENDES',3,'MUNTANER','MADRID');

INSERT INTO  EMPLEATS VALUES (3,'MANEL',250000,'MADRID',5,null);

select * from empleats, departaments;

select d.NUM_DPT, d.NOM_DPT, avg(e.sou) as SOU from departaments d, empleats e where d.NUM_DPT = e.NUM_DPT and CIUTAT_DPT = 'MADRID' group by d.NUM_DPT;