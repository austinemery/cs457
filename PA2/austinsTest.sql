DROP DATABASE test;

CREATE DATABASE test;
USE test;
CREATE TABLE Product (pid int, name varchar(20), price float);

insert into Product values(1, 'Gizmo', 19.99);
insert into Product values(5, 'SuperGizmo', 49.99);

update Product 
set price = 14.99 
where name = 'Gizmo';

select name, price 
from Product 
where pid != 2;

.exit

