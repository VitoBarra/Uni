var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
var Fuel;
(function (Fuel) {
    Fuel[Fuel["Diesel"] = 0] = "Diesel";
    Fuel[Fuel["Gasoline"] = 1] = "Gasoline";
    Fuel[Fuel["Electric"] = 2] = "Electric";
})(Fuel || (Fuel = {}));
;
var NoFuelException = /** @class */ (function (_super) {
    __extends(NoFuelException, _super);
    function NoFuelException() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return NoFuelException;
}(Error));
var Car = /** @class */ (function () {
    function Car(fuelType, fuelCapacity, consumption, fuelLevel) {
        if (fuelLevel === void 0) { fuelLevel = 0; }
        this.fuelType = fuelType;
        this.fuelCapacity = fuelCapacity;
        this.consumption = consumption;
        this.fuelLevel = fuelLevel;
    }
    Car.prototype.refillFuel = function (f) {
        this.fuelLevel = (f != undefined) ? ((this.fuelLevel + f) < this.fuelCapacity) ? this.fuelLevel + f : this.fuelCapacity : this.fuelCapacity;
        return this.fuelLevel;
    };
    Car.prototype.drive = function (km) {
        var TotalCon = km * this.consumption;
        console.log(TotalCon);
        if (TotalCon > this.fuelLevel)
            throw new NoFuelException();
        else {
            this.fuelLevel -= TotalCon;
            return this.fuelLevel;
        }
    };
    return Car;
}());
var c1 = new Car(Fuel.Diesel, 30, 0.5); // -> Car { fuelType: 0, fuelCapacity: 30, consumption: 0.5, fuelLevel: 0 }
console.log(c1.drive(10)); //-> lancia eccezione NoFuelException();
console.log(c1.refillFuel(20)); //->20
console.log(c1.drive(10)); //-> 15
console.log(c1.drive(30)); //-> 0
console.log(c1.refillFuel()); //->30
//# sourceMappingURL=Index.js.map