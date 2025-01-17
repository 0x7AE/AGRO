#define NUMBEROFBLOCKS 3

int main()
{
    int NumpadInput;

    int XY = 0;
    int LocationType = 0;

    int Coordinates[3][2][2]; //[Coordinate 1, 2 or 3][X or Y][Location or Destination]
    int CoordinatesFull[2][2];

    switch(NumpadInput)
    { 
       case(1):
        {
            //1
            if(CoordinatesFull[XY][LocationType] <= NUMBEROFBLOCKS)
            {
                Coordinates[CoordinatesFull[XY][LocationType]][XY][LocationType] = 1;
            }
            break;
        }
        case(2):
        {
            //2
            if(CoordinatesFull[XY][LocationType] <= NUMBEROFBLOCKS)
            {
                Coordinates[CoordinatesFull[XY][LocationType]][XY][LocationType] = 2;
            }
            break;
        }
        case(3):
        {
            //3
            if(CoordinatesFull[XY][LocationType] <= NUMBEROFBLOCKS)
            {
                Coordinates[CoordinatesFull[XY][LocationType]][XY][LocationType] = 3;
            }
            break;
        }
        case(4):
        {
            //A
            XY = 0;
            break;
        }
        case(5):
        {
            //4
            if(CoordinatesFull[XY][LocationType] <= NUMBEROFBLOCKS)
            {
                Coordinates[CoordinatesFull[XY][LocationType]][XY][LocationType] = 4;
            }
            break;
        }
        case(6):
        {
            //5
            if(CoordinatesFull[XY][LocationType] <= NUMBEROFBLOCKS)
            {
                Coordinates[CoordinatesFull[XY][LocationType]][XY][LocationType] = 5;
            }
            break;
        }
        case(7):
        {
            //6
            break;
        }
        case(8):
        {
            //B
            XY = 1;
            break;
        }
        case(9):
        {
            //7
            break;
        }
        case(10):
        {
            //8
            break;
        }
        case(11):
        {
           //9 UART_print("9\r\n");
            break;
        }
        case(12):
        {
            //C
            LocationType = 0;
            break;
        }
        case(13):
        {
            //*
            break;
        }
        case(14):
        {
            //0
            break;
        }
        case(15):
        {
            //#
            break;
        }
        case(16):
        {
            //D
            LocationType = 1;
            break;
        }
    }
}