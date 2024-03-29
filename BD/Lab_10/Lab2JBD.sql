drop table professors cascade;
drop table despatxos cascade;
drop table assignacions cascade;

create table professors
(dni char(50),
nomProf char(50) unique,
telefon char(15) unique,
sou integer,
primary key (dni));

create table despatxos
(modul char(5), 
numero char(5), 
superficie integer not null check(superficie>12 and superficie <25),
primary key (modul,numero));

create table assignacions
(dni char(50), 
modul char(5), 
numero char(5), 
instantInici integer, 
instantFi integer,
primary key (dni, modul, numero, instantInici),
foreign key (dni) references professors,
foreign key (modul,numero) references despatxos);

insert into professors values('111','ruth','3111',1000);
insert into professors values('222','ona','3222',1200);
insert into professors values('333','anna','3333',1100);
insert into professors values('444','mieria','3444',1300);

insert into despatxos values('omega','118',16);
insert into despatxos values('omega','128',20);
insert into despatxos values('c6','109',14);
insert into despatxos values('c6','120',14);
insert into despatxos values('u','125',13);

insert into assignacions values('111','u','125',0,108);
insert into assignacions values('111','c6','120',109,344);
insert into assignacions values('111','omega','128',345,365);
insert into assignacions values('333','omega','128',366,500);
insert into assignacions values('222','c6','109',109,344);
insert into assignacions values('222','omega','118',345,null);
insert into assignacions values('444','omega','118',345,380);


select * from despatxos;

