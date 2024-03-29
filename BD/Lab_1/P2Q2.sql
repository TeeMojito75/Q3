
CREATE TABLE DEPARTAMENTS
         (	NUM_DPT INTEGER PRIMARY KEY,
	NOM_DPT CHAR(20),
	PLANTA INTEGER,
	EDIFICI CHAR(30),
	CIUTAT_DPT CHAR(20));

CREATE TABLE PROJECTES(
    NUM_PROJ INTEGER PRIMARY KEY,
    NOM_PROJ CHAR(10),
    PRODUCTE CHAR(20),
    PRESSUPOST INTEGER
);

CREATE TABLE EMPLEATS
         (	NUM_EMPL INTEGER PRIMARY KEY,
	NOM_EMPL CHAR(30),
	SOU INTEGER,
	CIUTAT_EMPL CHAR(20),
	NUM_DPT INTEGER REFERENCES DEPARTAMENTS,
	NUM_PROJ INTEGER REFERENCES PROJECTES);

INSERT INTO  DEPARTAMENTS VALUES (3,'MARKETING',3,'RIOS ROSAS','BARCELONA');

INSERT INTO PROJECTES VALUEs (
2,'IBDVID','VIDEO',500000);

INSERT INTO  EMPLEATS VALUES (2,'ROBERTO',25000,'BARCELONA',3,2);

select * from departaments, projectes, empleats; 

select d.NOM_DPT, p.NOM_PROJ from departaments d, projectes p, empleats e where e.NUM_EMPL = 2 and e.NUM_PROJ = p.NUM_PROJ and e.NUM_DPT = d.NUM_DPT;