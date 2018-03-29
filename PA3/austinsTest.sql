DROP DATABASE test;

CREATE DATABASE test;
USE test;
CREATE TABLE Product (pid int, name varchar(20), price float);

insert into Product values(1, 'Gizmo', 19.99);
insert into Product values(2, 'Gagdet', 9.99);
insert into Product values(3, 'Car', 1119.99);
insert into Product values(4, 'Bike', 119.99);
insert into Product values(5, 'SuperGizmo', 49.99);

select pid, name, price 
from Product 
where pid >= 2;

select pid, name, price  
from Product 
where pid = 4;

select pid, name, price  
from Product 
where pid <= 3;

select pid, name, price  
from Product 
where pid != 3;

select pid, name, price  
from Product 
where pid > 4;

select pid, name, price  
from Product 
where pid < 2;

delete from PRODUCt 
Where pid >= 1;

insert into Product values(1, 'Gizmo', 19.99);
insert into Product values(2, 'Gagdet', 9.99);
insert into Product values(3, 'Car', 1119.99);
insert into Product values(4, 'Bike', 119.99);
insert into Product values(5, 'SuperGizmo', 49.99);

delete from PRODUCt 
Where pid >= 3;

select pid, name, price  
from Product 
where pid < 3;

.exit
