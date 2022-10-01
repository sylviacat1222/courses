SELECT ROUND(AVG(O.temp), 2) AS avg_temp, ROUND(AVG(O.humidity), 2) AS avg_humidity, ROUND(AVG(O.wind_speed), 2) AS avg_wind_speed, AVG(O.precipitation) AS avg_precipitation
FROM one_year O, (SELECT DISTINCT O.station_id
FROM one_year O, (SELECT DISTINCT S.station_id
FROM attraction A, station S
WHERE A.name LIKE '%台灣金屬創意館%' OR A.keyword LIKE '%金屬%' #要根據留言板內容調整
ORDER BY SQRT((A.px-S.px)*(A.px-S.px)+(A.py-S.py)*(A.py-S.py))
limit 10) AS stations
WHERE O.station_id = stations.station_id
limit 1) AS the_station
WHERE O.station_id = the_station.station_id AND MONTH(date) = 6 AND (DAY(date) = 2 OR DAY(date) = 3 OR DAY(date) = 4) AND O.date NOT LIKE '% 00:00:00'#日期根據留言版調整，不取第一筆，要注意是否月底月出


SELECT *
FROM
(SELECT N.name,  MIN(N.distance) AS m
FROM 
(SELECT SQRT((attraction.Px-station.px)*(attraction.Px-station.px)+(attraction.Py-station.py)*(attraction.Py-station.py)) AS distance, attraction.name , station.station_name , station.station_id, attraction.id FROM attraction, station) AS N
GROUP BY N.name) AS s,
(SELECT SQRT((attraction.Px-station.px)*(attraction.Px-station.px)+(attraction.Py-station.py)*(attraction.Py-station.py)) AS distance, attraction.name , station.station_name , station.station_id, attraction.id FROM attraction, station) AS N 
WHERE N.distance = s.m AND N.name = s.name

SELECT*
FROM
	(SELECT station_id 
	 FROM one_year 
	 WHERE pressure >= '1010.4' AND pressure <= '1010.4' AND
	       temp >= '23.1' AND temp <= '23.1' AND
	       humidity >= '97.0' AND humidity <= '97.0' AND
	       wind_speed LIKE BINARY '%0.3%' AND 
	       wind_dir LIKE BINARY '%北北東,NNE%'
	 group by station_id) AS A,
	(SELECT s.name, N.station_id
	 FROM (SELECT N.name,  MIN(N.distance) AS m
		   FROM (SELECT SQRT((attraction.Px-station.px)*(attraction.Px-station.px)+(attraction.Py-station.py)*(attraction.Py-station.py)) AS distance, 
						attraction.name , station.station_name , station.station_id, attraction.id
				 FROM attraction, station) AS N
		   GROUP BY N.name) AS s,
		  (SELECT SQRT((attraction.Px-station.px)*(attraction.Px-station.px)+(attraction.Py-station.py)*(attraction.Py-station.py)) AS distance, 
			attraction.name , station.station_name , station.station_id, attraction.id 
		   FROM attraction, station) AS N 
	WHERE N.distance = s.m AND N.name = s.name) AS B
WHERE A.station_id =B.station_id