enum Fuel {Diesel, Gasoline, Electric};

class NoFuelException extends Error
{

}


class Car 
{

    fuelType:Fuel;
    fuelCapacity :number;
    consumption : number;
    fuelLevel : number;

    constructor(fuelType:Fuel,fuelCapacity:number,consumption:number,fuelLevel:number=0)
    {
        this.fuelType =fuelType;
        this.fuelCapacity =fuelCapacity;
        this.consumption =consumption;
        this.fuelLevel =fuelLevel;
    }


    refillFuel(f?:number) :number
    {
        this.fuelLevel= (f !=undefined)?((this.fuelLevel+f)<this.fuelCapacity)? this.fuelLevel+f : this.fuelCapacity :this.fuelCapacity;
        return this.fuelLevel;
    }

    drive (km:number):number
    {
        let TotalCon = km*this.consumption;

        console.log(TotalCon);
        if(TotalCon > this.fuelLevel)
            throw new NoFuelException();
        else
        {
            this.fuelLevel -= TotalCon;
            return this.fuelLevel;
        }
    }
}