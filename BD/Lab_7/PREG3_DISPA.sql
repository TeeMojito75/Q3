drop table productes cascade;
drop table domicilis cascade;
drop table comandes cascade;
drop table liniesComandes cascade;
drop function func() cascade;

create table productes
(idProducte char(9),
nom char(20),
mida char(20),
preu integer check(preu>0),
primary key (idProducte),
unique (nom,mida));

create table domicilis
(numTelf char(9),
nomCarrer char(20),
numCarrer integer check(numCarrer>0),
pis char(2),
porta char(2),
primary key (numTelf));

create table comandes
(numComanda integer check(numComanda>0),
instantFeta integer not null check(instantFeta>0),
instantServida integer check(instantServida>0),
numTelf char(9),
import integer ,
primary key (numComanda),
foreign key (numTelf) references domicilis,
check (instantServida>instantFeta));
-- numTelf es el numero de telefon del domicili des don sha 
-- fet la comanda. Pot tenir valor nul en cas que la comanda 
-- sigui de les de recollir a la botiga. 

create table liniesComandes
(numComanda integer,
idProducte char(9),
quantitat integer check(quantitat>0),
primary key(numComanda,idProducte),
foreign key (idProducte) references productes,
foreign key (numComanda) references comandes
);
-- quantitat es el numero d'unitats del producte que sha demanat 
-- a la comanda

insert into productes values ('p111', '4 formatges', 'gran', 10);   

insert into productes values ('p222', 'margarita', 'gran', 5);  
 
insert into comandes(numComanda,instantfeta,instantservida,numtelf, import) values (110, 1091, 1101, null, 10);

insert into liniesComandes values (110, 'p222', 2);

CREATE OR replace FUNCTION func()RETURNS TRIGGER as $$
declare 
	idProd char(9);
	aux integer; ---Preu per fer correcció import
	newvalue integer; --qtt per fer correcció import
	aux_c integer;
begin 
	select idProducte into idProd from productes where idProducte = new.idProducte;
	select preu into aux from productes where idProducte = idProd;
	select quantitat into newvalue from liniesComandes where idProducte = idProd;
	select numComanda into aux_c from liniesComandes where numComanda = new.numComanda and idProducte = idProd;
	update comandes set import = import+(aux*newvalue*new.quantitat) where numComanda = aux_c;
	Return null;
end

$$LANGUAGE plpgsql;CREATE OR replace FUNCTION func()RETURNS TRIGGER as $$
declare 
	idProd char(9);
	aux integer; ---Preu per fer correcció import
	newvalue integer; --qtt per fer correcció import
	aux_c integer;
begin 
	select idProducte into idProd from productes where idProducte = new.idProducte;
	select preu into aux from productes where idProducte = idProd;
	select quantitat into newvalue from liniesComandes where idProducte = idProd;
	select numComanda into aux_c from liniesComandes where numComanda = new.numComanda and idProducte = idProd;
	update comandes set import = import+(aux*newvalue*new.quantitat) where numComanda = aux_c;
	Return null;
end

$$LANGUAGE plpgsql;


CREATE TRIGGER actu_import AFTER insert on liniesComandes for each row execute procedure func();



CREATE TRIGGER actu_import AFTER insert on liniesComandes for each row execute procedure func();

select * from comandes;
