drop table socis cascade;
drop table clubs cascade;
drop table socisclubs;
drop table missatgesexcepcions;
drop table clubs_amb_mes_de_5_socis;

create table socis ( nsoci char(10) primary key, sexe char(1) not null);

create table clubs ( nclub char(10) primary key);

create table socisclubs (nsoci char(10) not null references socis, 
  nclub char(10) not null references clubs, 
  primary key(nsoci, nclub));

create table clubs_amb_mes_de_5_socis (nclub char(10) primary key references clubs);

create table missatgesExcepcions(
	num integer, 
	texte varchar(50)
	);

	
	
insert into missatgesExcepcions values(1, 'Club amb mes de 10 socis');
insert into missatgesExcepcions values(2, 'Club amb mes homes que dones');
insert into missatgesExcepcions values(3, 'Soci ja assignat a aquest club');
insert into missatgesExcepcions values(4, 'O el soci o el club no existeixen');
insert into missatgesExcepcions values(5, 'Error intern');

insert into clubs values ('escacs');
insert into clubs values ('petanca');

insert into socis values ('anna','F');

insert into socis values ('joanna','F');
insert into socis values ('josefa','F');
insert into socis values ('pere','M');

insert into socisclubs values('joanna','petanca');
insert into socisclubs values('josefa','petanca');
insert into socisclubs values('pere','petanca');

create or replace FUNCTION assignar_individual(nomSoci char(10), nomClub char(10)) RETURNS VOID AS $$
	DECLARE
		contador integer;
		mujeres integer;
		missatge varchar(50);
	BEGIN
	
		INSERT INTO socisClubs values (nomSoci, nomClub);

		select count(*) into contador from socisclubs where nomClub = nclub;

		if (contador > 10) then
			select texte into missatge from missatgesexcepcions where num = 1;
		 	RAISE EXCEPTION '%', missatge;
		
		else 
			if (contador > 5) and not exists(select * from clubs_amb_mes_de_5_socis where nclub = nomClub) then
			insert into clubs_amb_mes_de_5_socis values(nomClub);
			end if;
			
			select count(*) into mujeres from socis s, socisclubs c where s.sexe = 'F' and s.nsoci = c.nsoci and nomClub = c.nclub;
			if (contador - mujeres > mujeres) then
				select texte into missatge from missatgesexcepcions where num = 2;
				raise exception '%', missatge;
			end if;
		end if;
	
	exception
		when raise_exception then
			raise exception '%', SQLERRM;
		when foreign_key_violation then
			select texte into missatge from missatgesexcepcions where num = 4;
			raise exception '%', missatge;
		when unique_violation then
			select texte into missatge from missatgesexcepcions where num = 3;
			raise exception '%', missatge;
		when others then
			select texte into missatge from missatgesexcepcions where num = 5;
			raise exception '%', missatge;
	end;
$$LANGUAGE plpgsql;

 select * from assignar_individual('anna','escacs'); 
 
select * from socisclubs;
