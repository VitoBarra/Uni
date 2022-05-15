type btree =
| Void
| Node of int * btree * btree



let rec count bt p =
match bt with 
| (x,Void,Void) -> if(p x) then 1 else 0
| (x,N1,N2) -> count N1 p+ count N2 p + if(p x) then 1 else 0


let positivo x =
match x with
| Void -> false
| Node (i,_,_) -> i>0

let bt =
Node (3,
Node (5,Void,Void),
Node (-4,
Node(6,Void,Void),
Node(8,Void,Void)))
count bt positivo