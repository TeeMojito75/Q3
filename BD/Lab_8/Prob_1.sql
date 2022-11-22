drop table empleats1;
drop table empleats2;

create table empleats1 (nemp1 integer primary key, nom1 char(25), ciutat1 char(10) not null);

create table empleats2 (nemp2 integer primary key, nom2 char(25), ciutat2 char(10) not null);

insert into empleats2 values(1,'joan','bcn');
insert into empleats2 values(2,'pere','mad');
insert into empleats2 values(3,'enric','bcn');
insert into empleats1 values(1,'joan','bcn');
insert into empleats1 values(2,'maria','mad');


create or replace function func() returns trigger as $$
	begin 
		if (not exists(select * from empleats2 where ciutat2 = old.ciutat2))
			then delete from empleats1 where ciutat1 = old.ciutat2;
	end if;
	return null;
end
$$LANGUAGE plpgsql;  


create trigger mod_ciutat after delete on empleats2 for each row execute procedure func();
create trigger mod_ciut after update of ciutat2 on empleats2 for each row execute procedure func();


 DELETE FROM empleats2 WHERE nemp2=1;
 
select * from empleats1 ;
select * from empleats2;
