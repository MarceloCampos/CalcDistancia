void setup() 
{

  Serial.begin(9600);
  /* Alcon aprox.:
      -23.5756539,-46.6174493
   padaria Poesia aprox. :
      -23.5738359,-46.6145222
   */

  long DistanciaMetros = CalcDistance( -23.5756539, -46.6174493, -23.5738359, -46.6145222 ) ;
  Serial.print(DistanciaMetros);

}

void loop() {
  

}


//convert degrees to radians
double dtor(double fdegrees)
{
  return(fdegrees * PI / 180);
}

//Convert radians to degrees
double rtod(double fradians)
{
  return(fradians * 180.0 / PI);
}

//Calculate distance form lat1/lon1 to lat2/lon2 using haversine formula
//Note lat1/lon1/lat2/lon2 must be in radians
//Returns distance in feet
long CalcDistance(double lat1, double lon1, double lat2, double lon2)
{
double dlon, dlat, a, c;
double dist = 0.0;
dlon = dtor(lon2 - lon1);
dlat = dtor(lat2 - lat1);
a = pow(sin(dlat/2),2) + cos(dtor(lat1)) * cos(dtor(lat2)) * pow(sin(dlon/2),2);
c = 2 * atan2(sqrt(a), sqrt(1-a));

dist = 20925656.2 * c;  //radius of the earth (6378140 meters) in feet 20925656.2
return( (long) dist + 0.5);
}

//Calculate bearing from lat1/lon1 to lat2/lon2
//Note lat1/lon1/lat2/lon2 must be in radians
//Returns bearing in degrees
int CalcBearing(double lat1, double lon1, double lat2, double lon2)
{
lat1 = dtor(lat1);
lon1 = dtor(lon1);
lat2 = dtor(lat2);
lon2 = dtor(lon2);

//determine angle
double bearing = atan2(sin(lon2-lon1)*cos(lat2), (cos(lat1)*sin(lat2))-(sin(lat1)*cos(lat2)*cos(lon2-lon1)));
//convert to degrees
bearing = rtod(bearing);
//use mod to turn -90 = 270
bearing = fmod((bearing + 360.0), 360);
return (int) bearing + 0.5;
}

void ComputeDestPoint(double lat1, double lon1, int iBear, int iDist, double *lat2, double *lon2)
{
double bearing = dtor((double) iBear);
double dist = (double) iDist / 20925656.2;
lat1 = dtor(lat1);
lon1 = dtor(lon1);
*lat2 = asin(sin(lat1)* cos(dist)+ cos(lat1)* sin(dist)*cos(bearing));
*lon2 = lon1 + atan2(sin(bearing)*sin(dist)*cos(lat1), cos(dist)-sin(lat1)*sin(*lat2));
*lon2 = fmod( *lon2 + 3 * PI, 2*PI )- PI;
*lon2 = rtod( *lon2);
*lat2 = rtod( *lat2);
}

