-- Sentències de preparació de la base de dades:
create table empleats(
                 nempl integer primary key,
                 salari integer);

create table missatgesExcepcions(
	num integer, 
	texte varchar(100));

insert into missatgesExcepcions values(1,'No es pot esborrar l''empleat 123 ni modificar el seu número d''empleat');

-- Sentències d'esborrat de la base de dades:
drop table empleats;
drop table missatgesExcepcions;

--------------------------
-- Joc de proves Public
--------------------------

-- Sentències d'inicialització:
insert into empleats values(1,1000);
insert into empleats values(2,2000);
insert into empleats values(123,3000);

-- Dades d'entrada o sentències d'execució:
delete from empleats where nempl=123;
drop function func();


CREATE FUNCTION func() RETURNS trigger as $$
DECLARE
	missatge varchar(100);
BEGIN
	if (old.nempl = 123) then
		SELECT texte INTO missatge FROM missatgesExcepcions WHERE num=1;
		RAISE EXCEPTION '%',missatge;
	else
		if(tg_op = 'DELETE') then return old;
		else if (tg_op = 'UPDATE') then return new;
		end if;
	end if;
end if;
END;
$$LANGUAGE plpgsql;


CREATE TRIGGER restriccio BEFORE DELETE ON empleats for each row EXECUTE PROCEDURE func();
CREATE TRIGGER restriccio_1 BEFORE UPDATE of nempl on empleats for each row EXECUTE PROCEDURE func();


 DELETE FROM empleats WHERE nempl=123; 
UPDATE empleats set nempl = nempl + 1 where nempl = 123;







