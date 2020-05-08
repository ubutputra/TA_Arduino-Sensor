BEGIN

DECLARE ba_co INT DEFAULT 0;
DECLARE bb_co INT DEFAULT 0;
DECLARE ba_temperature INT DEFAULT 0;
DECLARE bb_temperature INT DEFAULT 0;
DECLARE ba_humidity INT DEFAULT 0;
DECLARE bb_humidity INT DEFAULT 0;
DECLARE ba_gas INT DEFAULT 0;
DECLARE bb_gas INT DEFAULT 0;
DECLARE jumlah_data_ba_temperature INT DEFAULT 0;
DECLARE jumlah_data_bb_temperature INT DEFAULT 0;
DECLARE jumlah_data_ba_humidity INT DEFAULT 0;
DECLARE jumlah_data_bb_humidity INT DEFAULT 0;
DECLARE jumlah_data_ba_gas INT DEFAULT 0;
DECLARE jumlah_data_bb_gas INT DEFAULT 0;
DECLARE jumlah_data_ba_co INT DEFAULT 0;
DECLARE jumlah_data_bb_co INT DEFAULT 0;

--variable informasi sensor
DECLARE info_temperature VARCHAR(40);
DECLARE info_humidity VARCHAR(40);
DECLARE info_gas VARCHAR(40);
DECLARE info_co VARCHAR(40);

-- set variable ba dan bb masing2 sensor
SET ba_temperature = (SELECT ba_temperature FROM rulebase order by id desc LIMIT 1);
SET bb_temperature = (SELECT bb_temperature FROM rulebase ORDER BY id DESC LIMIT 1);
SET ba_humidity = (SELECT ba_humidity FROM rulebase ORDER BY id DESC LIMIT 1);
SET bb_humidity = (SELECT bb_humidity FROM rulebase ORDER BY id DESC LIMIT 1);
SET ba_gas = (SELECT ba_gas FROM rulebase ORDER BY id DESC LIMIT 1);
SET bb_gas = (SELECT bb_gas FROM rulebase ORDER BY id DESC LIMIT 1);
SET ba_co = (SELECT ba_co FROM rulebase ORDER BY id DESC LIMIT 1);
SET bb_co = (SELECT bb_co FROM rulebase ORDER BY id DESC LIMIT 1);


--mulai perhitungan rulebase temperature
set jumlah_data_ba_temperature = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_dht11_temperature > ba_temperature);
set jumlah_data_bb_temperature = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_dht11_temperature < bb_temperature);

IF jumlah_data_ba_temperature > jumlah_data_bb_temperature THEN
    set info_temperature = (SELECT informasi_ba_temperature FROM rulebase ORDER BY id DESC LIMIT 1);
ELSEIF jumlah_data_ba_temperature < jumlah_data_bb_temperature THEN
    set info_temperature = (SELECT informasi_bb_temperature FROM rulebase ORDER BY id DESC LIMIT 1);
ELSE 
    set info_temperature = 'normal';
END IF;

--mulai perhitungan rule base humidity
set jumlah_data_ba_humidity = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_dht11_humidity > ba_humidity);
set jumlah_data_bb_humidity = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_dht11_humidity < bb_humidity);

IF jumlah_data_ba_humidity > jumlah_data_bb_humidity THEN
    set info_humidity = (SELECT informasi_ba_humidity FROM rulebase ORDER BY id DESC LIMIT 1);
ELSEIF jumlah_data_ba_humidity < jumlah_data_bb_humidity THEN
    set info_humidity = (SELECT informasi_bb_humidity FROM rulebase ORDER BY id DESC LIMIT 1);
ELSE 
    set info_humidity = 'normal';
END IF;

--mulai perhitungan rule base gas
set jumlah_data_ba_gas = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_mq135 > ba_gas);
set jumlah_data_bb_gas = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_mq135 < bb_gas);

IF jumlah_data_ba_gas > jumlah_data_bb_gas THEN
    set info_gas = (SELECT informasi_ba_gas FROM rulebase ORDER BY id DESC LIMIT 1);
ELSEIF jumlah_data_ba_gas < jumlah_data_bb_gas THEN
    set info_gas = (SELECT informasi_bb_gas FROM rulebase ORDER BY id DESC LIMIT 1);
ELSE 
    set info_gas = 'normal';
END IF;

--mulai perhitungan rule base gas CO
set jumlah_data_ba_co = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_mq7 > ba_co);
set jumlah_data_bb_co = (SELECT COUNT(*) FROM (SELECT * from data_sensor WHERE id_node = id_node ORDER BY created_at DESC LIMIT 50) AS d where d.data_mq7 < bb_co);

IF jumlah_data_ba_co > jumlah_data_bb_co THEN
    set info_co = (SELECT informasi_ba_co FROM rulebase ORDER BY id DESC LIMIT 1);
ELSEIF jumlah_data_ba_co < jumlah_data_bb_co THEN
    set info_co = (SELECT informasi_bb_co FROM rulebase ORDER BY id DESC LIMIT 1);
ELSE 
    set info_co = 'normal';
END IF;

INSERT INTO info_rulebase (id_node,info_rulebase_temperature,info_rulebase_humidity,info_rulebase_gas,info_rulebase_co)
VALUES (id_node,info_temperature,info_humidity,info_gas,info_co );

SELECT concat('info temperature is ',info_temperature);
SELECT concat('info humidity is ',info_humidity);
SELECT concat('info gas is ',info_gas);
SELECT concat('info co is ',info_co);

END