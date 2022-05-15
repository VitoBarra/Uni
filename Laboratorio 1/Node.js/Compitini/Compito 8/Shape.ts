interface Shape {
  x: number;
  y: number;
  area(): number;
  getName(): string;
  translate(x: number, y: number): void;
}

class Circle implements Shape {
  x: number = 1;
  y: number = 1;
  ragio: number = 1;
  name: string;
  constructor(x: number = 1, y: number = 1, l: number = 1) {
    if (y > 0) this.y = y;
    if (x > 0) this.x = x;
    if (l) this.ragio = l;
    this.name = "Square";
  }

  area(): number {
    return this.ragio ** 2 * Math.PI;
  }
  getName(): string {
    return this.name;
  }
  translate(x: number, y: number): void {
    this.x = x;
    this.y = y;
  }
}

class Square implements Shape {
  x: number = 1;
  y: number = 1;
  lato: number = 1;
  name: string;
  constructor(x: number = 1, y: number = 1, l: number = 1) {
    if (y > 0) this.y = y;
    if (x > 0) this.x = x;
    if (l) this.lato = l;
    this.name = "Circle";
  }

  area(): number {
    return this.lato ** 2;
  }
  getName(): string {
    return this.name;
  }
  translate(x: number, y: number): void {
    this.x = x;
    this.y = y;
  }
}

let c1 = new Circle(0, 0, 2); // -> Circle { x: 0, y: 0, r: 2 }
console.log(c1.area()); // -> 12.566370614359172
c1.translate(1, -0.5);
console.log(c1); //-> Circle { x: 1, y: -0.5, r: 2 }
console.log(c1.getName()); //-> 'Circle'

let c2 = new Circle(10, 1, 0.5); // -> Circle { x: 100, y: -100, r: 0.5 }
console.log(c2.area()); // -> 0.7853981633974483
console.log(c2.translate(100, -100)); //-> Circle { x: 100, y: -100, r: 0.5 }

let q1 = new Square(1, 0, 10); // -> Square { x: 1, y: 0, l: 10 }}
console.log(q1.area()); // -> 100
q1.translate(-4.8, -3.5);
console.log(q1); //-> Square { x: -4.8, y: -3.5, l: 10 }
console.log(q1.getName()); //-> 'Square'

let q2 = new Square(0, 0, 0); // -> Square { x: 0, y: 0, l: 1 }
console.log(q2.area()); // -> 1
console.log(q2.translate(1, 1)); //-> Square { x: 1, y: 1, l: 1 }
