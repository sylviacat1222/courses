CREATE TABLE tourist(
year INT,
type VARCHAR(20) COLLATE utf8_unicode_ci,
area VARCHAR(20) COLLATE utf8_unicode_ci,
spot VARCHAR(20) COLLATE utf8_unicode_ci NOT NULL,
city VARCHAR(3) COLLATE utf8_unicode_ci,
jan INT,
feb INT,
mar INT,
apr INT,
may INT,
jun INT,
jul INT,
aug INT,
sep INT,
oct INT,
nov INT,
d INT,
summation INT,
PRIMARY KEY(year, spot)
);



LOAD DATA LOCAL INFILE '/home/sylvia/final_project/tourist_2.csv'
INTO TABLE tourist
CHARACTER SET utf8mb4
FIELDS TERMINATED BY ','
ENCLOSED BY '"'
LINES TERMINATED BY '\n'
IGNORE 1 ROWS;

SELECT *
from tourist
WHERE jan = 11552;

DROP TABLE tourist;
