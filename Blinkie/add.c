struct timeb start_time_mili,new_time_mili;
ftime (&start_time_mili);
ftime (&new_time_mili);
//TODO:new:
int diff=1000 - start_time_mili;

//time_t end_t = time(NULL);
int counter=0;
//TODO:new
while ( (1000*(new_time_mili.time - start_time_mili.time) + (new_time_mili.millis + diff - new_time_mili.millis)) < 999)
{
        //if counter value goes above 20 (21) reset it
        if (counter > 20)
        {
                counter = 0;
        }

        counter=counter+1;

//get the actual time in millisecconds
        ftime(&new_time_mili);
//get the time elapsed since method was called
//TODO:new
        int time_lapsed= (new_time_mili.millitm + diff - start_time_mili.millitm) * 1000 ;

// wiringPi frequency is ~ 4.1MHz ~ 4100000 clock cicles / second
// it will be reduced due to math operations

//      #from 0 to 5% don't do nothing
if ( time_lapsed  < 5)
{
digitalWrite(led,LOW);

//led is off
"main.c.old" 164L, 2401C       
