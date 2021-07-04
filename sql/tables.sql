-- MySQL dump 10.13  Distrib 8.0.22, for Win64 (x86_64)
--
-- Host: localhost    Database: hospitalsystem
-- ------------------------------------------------------
-- Server version	8.0.22

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `bed_temp`
--

DROP TABLE IF EXISTS `bed_temp`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `bed_temp` (
  `bed_id` int NOT NULL,
  PRIMARY KEY (`bed_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `bed_temp`
--

LOCK TABLES `bed_temp` WRITE;
/*!40000 ALTER TABLE `bed_temp` DISABLE KEYS */;
/*!40000 ALTER TABLE `bed_temp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department`
--

DROP TABLE IF EXISTS `department`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `department` (
  `id` varchar(10) NOT NULL,
  `name` varchar(30) NOT NULL,
  `leader` varchar(10) DEFAULT NULL,
  `phone` varchar(20) NOT NULL,
  `address` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `leader_idx` (`leader`),
  CONSTRAINT `leader` FOREIGN KEY (`leader`) REFERENCES `doctor` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department`
--

LOCK TABLES `department` WRITE;
/*!40000 ALTER TABLE `department` DISABLE KEYS */;
INSERT INTO `department` VALUES ('10001','骨科',NULL,'11111111','1-101'),('10002','外科',NULL,'22222222','2-202'),('10003','儿科',NULL,'33333333','3-303'),('10004','心脑血管科',NULL,'44444444','4-404'),('10005','急诊科',NULL,'55555555','5-505');
/*!40000 ALTER TABLE `department` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `department_sickroom`
--

DROP TABLE IF EXISTS `department_sickroom`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `department_sickroom` (
  `department_id` varchar(10) NOT NULL,
  `sickroom_id` varchar(10) NOT NULL,
  PRIMARY KEY (`sickroom_id`),
  KEY `department_id5_idx` (`department_id`),
  CONSTRAINT `department_id5` FOREIGN KEY (`department_id`) REFERENCES `department` (`id`),
  CONSTRAINT `sickroom_id5` FOREIGN KEY (`sickroom_id`) REFERENCES `sickroom` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `department_sickroom`
--

LOCK TABLES `department_sickroom` WRITE;
/*!40000 ALTER TABLE `department_sickroom` DISABLE KEYS */;
INSERT INTO `department_sickroom` VALUES ('10001','1001'),('10001','1002'),('10002','1003'),('10002','1004'),('10003','1005'),('10003','1006'),('10003','1007'),('10003','1008'),('10004','1009'),('10004','1010');
/*!40000 ALTER TABLE `department_sickroom` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `doctor`
--

DROP TABLE IF EXISTS `doctor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `doctor` (
  `id` varchar(10) NOT NULL,
  `name` varchar(20) NOT NULL,
  `sex` char(2) NOT NULL,
  `age` int NOT NULL,
  `phone` char(11) NOT NULL,
  `department` varchar(10) NOT NULL,
  `professional` varchar(20) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `departement_idx` (`department`),
  CONSTRAINT `departement` FOREIGN KEY (`department`) REFERENCES `department` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doctor`
--

LOCK TABLES `doctor` WRITE;
/*!40000 ALTER TABLE `doctor` DISABLE KEYS */;
INSERT INTO `doctor` VALUES ('9001','马医生','男',69,'13390876544','10001','主任医师'),('9002','李医生','男',45,'19877775555','10002','主任医师'),('9003','王医生','女',30,'19988884444','10002','副主任医师'),('9004','张医生','男',56,'17866664444','10003','主治医师'),('9005','孔医生','女',50,'19988884444','10004','住院医师'),('9006','赵医生','男',34,'19977775555','10005','主任医师');
/*!40000 ALTER TABLE `doctor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `inspection_items`
--

DROP TABLE IF EXISTS `inspection_items`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `inspection_items` (
  `id` varchar(20) NOT NULL,
  `content` varchar(100) NOT NULL,
  `cost` double NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `inspection_items`
--

LOCK TABLES `inspection_items` WRITE;
/*!40000 ALTER TABLE `inspection_items` DISABLE KEYS */;
INSERT INTO `inspection_items` VALUES ('GUKE1007','一个检查项目',20),('WAIKE1002','一个检查',100),('WK1001','X光片',80);
/*!40000 ALTER TABLE `inspection_items` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patient`
--

DROP TABLE IF EXISTS `patient`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `patient` (
  `id` char(18) NOT NULL,
  `name` varchar(20) NOT NULL,
  `sex` char(2) NOT NULL,
  `age` int NOT NULL,
  `phone` char(11) NOT NULL,
  `address` varchar(100) NOT NULL,
  `start_time` datetime NOT NULL,
  `sickroom_id` varchar(10) NOT NULL,
  `bed_id` varchar(2) NOT NULL,
  `account` double NOT NULL,
  `sum_bed_cost` double NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `sickroom_id_idx` (`sickroom_id`),
  CONSTRAINT `sickroom_id` FOREIGN KEY (`sickroom_id`) REFERENCES `sickroom` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patient`
--

LOCK TABLES `patient` WRITE;
/*!40000 ALTER TABLE `patient` DISABLE KEYS */;
INSERT INTO `patient` VALUES ('410901200108100010','孔','男',20,'18639302509','卫河佳苑','2021-01-15 11:26:50','1004','1',10000,0),('410922200033334444','用户视图测试','女',21,'17788884444','山东大学','2021-01-10 23:08:36','1001','1',70,0),('410922200101018888','测试病人一','男',19,'18877776666','凤凰居','2020-12-14 22:45:24','1003','1',390,1600),('410922200211116789','用户测试','男',19,'16655557777','山大','2021-01-10 23:11:59','1003','2',-20,0);
/*!40000 ALTER TABLE `patient` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patient_doctor`
--

DROP TABLE IF EXISTS `patient_doctor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `patient_doctor` (
  `patient_id` char(18) NOT NULL,
  `doctor_id` varchar(10) NOT NULL,
  PRIMARY KEY (`patient_id`),
  KEY `patient_doctor_doctor_id_idx` (`doctor_id`),
  CONSTRAINT `doctor_id1` FOREIGN KEY (`doctor_id`) REFERENCES `doctor` (`id`),
  CONSTRAINT `patient_id1` FOREIGN KEY (`patient_id`) REFERENCES `patient` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patient_doctor`
--

LOCK TABLES `patient_doctor` WRITE;
/*!40000 ALTER TABLE `patient_doctor` DISABLE KEYS */;
INSERT INTO `patient_doctor` VALUES ('410922200033334444','9001'),('410922200211116789','9002'),('410901200108100010','9003');
/*!40000 ALTER TABLE `patient_doctor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patient_inspection`
--

DROP TABLE IF EXISTS `patient_inspection`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `patient_inspection` (
  `patient_id` char(18) NOT NULL,
  `inspection_id` varchar(20) NOT NULL,
  `place` varchar(50) NOT NULL,
  PRIMARY KEY (`inspection_id`),
  KEY `patient_id2_idx` (`patient_id`),
  CONSTRAINT `inspection_id2` FOREIGN KEY (`inspection_id`) REFERENCES `inspection_items` (`id`),
  CONSTRAINT `patient_id2` FOREIGN KEY (`patient_id`) REFERENCES `patient` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patient_inspection`
--

LOCK TABLES `patient_inspection` WRITE;
/*!40000 ALTER TABLE `patient_inspection` DISABLE KEYS */;
INSERT INTO `patient_inspection` VALUES ('410922200033334444','GUKE1007','3-303'),('410922200211116789','WAIKE1002','2-202');
/*!40000 ALTER TABLE `patient_inspection` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patient_payment`
--

DROP TABLE IF EXISTS `patient_payment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `patient_payment` (
  `patient_id` char(18) NOT NULL,
  `payment_id` varchar(20) NOT NULL,
  PRIMARY KEY (`payment_id`),
  KEY `patient_id3_idx` (`patient_id`),
  CONSTRAINT `patient_id3` FOREIGN KEY (`patient_id`) REFERENCES `patient` (`id`),
  CONSTRAINT `payment_id3` FOREIGN KEY (`payment_id`) REFERENCES `payment` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patient_payment`
--

LOCK TABLES `patient_payment` WRITE;
/*!40000 ALTER TABLE `patient_payment` DISABLE KEYS */;
/*!40000 ALTER TABLE `patient_payment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patient_prescription`
--

DROP TABLE IF EXISTS `patient_prescription`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `patient_prescription` (
  `patient_id` char(18) NOT NULL,
  `prescription_id` varchar(20) NOT NULL,
  PRIMARY KEY (`prescription_id`),
  KEY `patient_id4_idx` (`patient_id`),
  CONSTRAINT `patient_id4` FOREIGN KEY (`patient_id`) REFERENCES `patient` (`id`),
  CONSTRAINT `prescription_id4` FOREIGN KEY (`prescription_id`) REFERENCES `prescription` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patient_prescription`
--

LOCK TABLES `patient_prescription` WRITE;
/*!40000 ALTER TABLE `patient_prescription` DISABLE KEYS */;
INSERT INTO `patient_prescription` VALUES ('410922200033334444','GUKE1007'),('410922200101018888','WAIKE1001'),('410922200211116789','WAIKE1002');
/*!40000 ALTER TABLE `patient_prescription` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `payback`
--

DROP TABLE IF EXISTS `payback`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `payback` (
  `id` int NOT NULL AUTO_INCREMENT,
  `patient_id` char(18) NOT NULL,
  `amount` double NOT NULL,
  `time` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1000000012 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `payback`
--

LOCK TABLES `payback` WRITE;
/*!40000 ALTER TABLE `payback` DISABLE KEYS */;
INSERT INTO `payback` VALUES (1000000004,'410901200109099999',2000,'2020-12-15 09:16:28'),(1000000005,'410922200012120091',1000,'2021-01-10 22:55:12'),(1000000006,'410922200012120091',1000,'2021-01-10 22:55:31'),(1000000007,'410922200012120091',1000,'2021-01-10 22:56:51'),(1000000008,'410922200012120091',1000,'2021-01-10 22:57:04'),(1000000009,'410922200012120091',1000,'2021-01-10 22:59:39'),(1000000010,'410922200101018888',390,'2021-01-10 22:59:57'),(1000000011,'410922200303034466',290,'2021-01-11 00:12:25');
/*!40000 ALTER TABLE `payback` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `payment`
--

DROP TABLE IF EXISTS `payment`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `payment` (
  `id` varchar(20) NOT NULL,
  `amount` double NOT NULL,
  `time` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `payment`
--

LOCK TABLES `payment` WRITE;
/*!40000 ALTER TABLE `payment` DISABLE KEYS */;
INSERT INTO `payment` VALUES ('10001',90,'2021-01-10 22:54:27'),('123',700,'2021-01-10 23:00:37'),('700',0,'2021-01-10 23:00:13'),('JIAOFEI1001',100,'2021-01-11 00:06:57');
/*!40000 ALTER TABLE `payment` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `prescription`
--

DROP TABLE IF EXISTS `prescription`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `prescription` (
  `id` varchar(20) NOT NULL,
  `content` varchar(200) NOT NULL,
  `doctor` varchar(10) NOT NULL,
  `cost` double NOT NULL,
  PRIMARY KEY (`id`),
  KEY `doctor_idx` (`doctor`),
  CONSTRAINT `doctor` FOREIGN KEY (`doctor`) REFERENCES `doctor` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prescription`
--

LOCK TABLES `prescription` WRITE;
/*!40000 ALTER TABLE `prescription` DISABLE KEYS */;
INSERT INTO `prescription` VALUES ('GUKE1001','板蓝根1袋，感冒颗粒1盒','9001',20),('GUKE1002','连花清瘟胶囊1盒','9001',60),('GUKE1007','一个处方','9001',10),('GUKE1111','处方1','9001',10),('WAIKE1001','绷带','9002',10),('WAIKE1002','一个处方','9002',20),('WK1001','绷带*1','9002',10);
/*!40000 ALTER TABLE `prescription` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `sickroom`
--

DROP TABLE IF EXISTS `sickroom`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `sickroom` (
  `id` varchar(10) NOT NULL,
  `patient_number` int NOT NULL,
  `capacity` int NOT NULL,
  `rank` varchar(20) NOT NULL,
  `cost_per_day` double NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `sickroom`
--

LOCK TABLES `sickroom` WRITE;
/*!40000 ALTER TABLE `sickroom` DISABLE KEYS */;
INSERT INTO `sickroom` VALUES ('1001',0,4,'普通病房',100),('1002',-4,1,'ICU病房',500),('1003',1,4,'普通病房',100),('1004',1,1,'ICU病房',500),('1005',0,4,'普通病房',100),('1006',0,1,'ICU病房',500),('1007',0,4,'普通病房',100),('1008',1,4,'普通病房',100),('1009',0,4,'普通病房',100),('1010',0,4,'普通病房',100);
/*!40000 ALTER TABLE `sickroom` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2021-04-03 10:53:56
