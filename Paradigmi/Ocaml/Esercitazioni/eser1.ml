let  duemax lis =
let rec aux li pm =
    match li with
    | [] -> None
    | x::[] -> ( match pm with 
                | (z,h) -> if (z<x) then Some (x,z) else 
                           if (h<x) then Some (z,x)  else Some l' pm )
    | x::l' -> match pm with +
        | (z,h) -> if (z<x) then aux l' (x,z) else 
                if (h<x) then aux l' (z,x)  else aux l' pm 
in
aux lis (~-10000,~-10000);;


duemax [4;6;2;1;6];;



let max lis =
let greater n n2 = if(n>=n2) then n else n2 in
let rec aux li pm =
match li with
| [] -> None
| x::[] -> let m = greater x pm in Some m
| x::l' -> let m = greater x pm  in aux l' m
in
(aux lis ~-10000);;

max [4;6;2;1;6];;