# import xml element tree
import xml.etree.ElementTree as ET
  
# import mysql connector
import mysql.connector
  
# give the connection parameters
# user name is root
# password is empty
# server is localhost
# database name is database
conn = mysql.connector.connect(user='root', 
                               password='', 
                               host='localhost', 
                               database='final_project')
  
# reading xml file , file name is vignan.xml
tree = ET.parse('dy_Report_2020.xml')
  
# in our xml file student is the root for all 
# student data.
data2 = tree.findall('data')
  
# retrieving the data and insert into table
# i value for xml data #j value printing number of 
# values that are stored
for i, j in zip(data2, range(1, 6)):
    stationName = i.find('stationName').text
    dataDate = i.find('dataDate').text
    precipitation = i.find('precipitation').text
      
    # sql query to insert data into database
    data = """INSERT INTO dy_Report_2020(stationName,dataDate,precipitation) VALUES(%s,%s,%s)"""
  
    # creating the cursor object
    c = conn.cursor()
      
    # executing cursor object
    c.execute(data, (stationName, dataDate, precipitation))
    conn.commit()
    print("dy_Report_2020 data No-", j, " stored successfully")