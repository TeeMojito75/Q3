drop table empleats;
drop table dia;
drop table missatgesexcepcions;
drop function func();

CREATE TABLE empleats(
  nempl integer primary key,
  salari integer);

insert into empleats values(1,1000);

insert into empleats values(2,2000);

insert into empleats values(123,3000);

CREATE TABLE dia(
dia char(10));

insert into dia values('dijous');

create table missatgesExcepcions(
	num integer, 
	texte varchar(50)
	);
insert into missatgesExcepcions values(1,'No es poden esborrar empleats el dijous');

CREATE FUNCTION func() RETURNS TRIGGER as $$
DECLARE
	missatge varchar(100);
	avui char(10);
BEGIN
	select dia into avui from dia;
	if (avui = 'dijous') then SELECT texte INTO missatge 
		FROM missatgesExcepcions WHERE num=1;
		RAISE EXCEPTION '%',missatge;
	else return old;
	end if;
END;
$$LANGUAGE plpgsql;


CREATE TRIGGER restriccio BEFORE DELETE ON empleats for each statement EXECUTE PROCEDURE func();
 
--Pel joc de proves que trobareu al fitxer adjunt i la instrucció:
DELETE FROM em0pleats WHERE salari<=1000;

 
