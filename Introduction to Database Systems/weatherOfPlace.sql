# 距離景點最近的十個測站id
SELECT DISTINCT S.station_id
FROM attraction A, station S
WHERE A.name LIKE '%台灣金屬創意館%' OR A.keyword LIKE '%金屬%' #要根據內容調整
ORDER BY SQRT((A.px-S.px)*(A.px-S.px)+(A.py-S.py)*(A.py-S.py))
limit 10

# 測站id有在one_year裡面，取最近的
SELECT DISTINCT O.station_id
FROM one_year O, (SELECT DISTINCT S.station_id
FROM attraction A, station S
WHERE A.name LIKE '%台灣金屬創意館%' OR A.keyword LIKE '%金屬%' #要根據留言板內容調整
ORDER BY SQRT((A.px-S.px)*(A.px-S.px)+(A.py-S.py)*(A.py-S.py))
limit 10) AS stations
WHERE O.station_id = stations.station_id
limit 1

#三天內的平均氣溫 濕度 風速 降雨
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

