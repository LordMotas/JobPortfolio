--Project Euler #24
--What is the millionth lexicographic permutation of 0123456789?

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler24 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  N : Integer := 9;
  subtype Element is Integer range 0 .. N;
  type Permutation is array(Element) of Element;
  
  procedure Set_To_First(P : out Permutation; Is_Last : out Boolean) is
  begin
    for I in P'Range loop
      P(I) := I;
    end loop;
    Is_Last := P'Length = 1;
    --if P has a single element, the first permutation is also the last one
  end Set_to_First;

  procedure Go_To_Next(P : in out Permutation; Is_Last : out Boolean) is
  
    procedure Swap (A, B : in out Integer) is
      C : Integer := A;
    begin
      A := B;
      B := C;
    end Swap;

    I, J, K : Element;
  begin
    Is_Last := True;
    I := N - 1;
    loop
      if P(I) < P(I+1) then
        Is_Last := False;
        exit;
      end if;
      exit when I = 0;
      I := I - 1;
    end loop;
  
    if Is_Last then
      return;
    end if;
  
    J := I + 1;
    K := N;
    while J < K loop
      Swap(P(J), P(K));
      J := J + 1;
      K := K - 1;
    end loop;
  
    J := N;
    while P(J) > P(I) loop
      J := J - 1;
    end loop;
    J := J + 1;
    
    Swap(P(I), P(J));
  end Go_To_Next;

  procedure Print(P : Permutation) is
  begin
    for I in P'Range loop
      IO.Put(Element'Image(P(I)));
    end loop;
    IO.New_Line;
  end Print;

  P : Permutation := (0 => 0, 1 => 1, 2 => 2, 3 => 3, 4 => 4, 5 => 5, 6 => 6, 7 => 7, 8 => 8, 9 => 9);
  Done : Boolean := False;
  Count : Integer := 0;
  
begin

  Set_To_First(P, Done);
  loop
    if Count = 1000000 then
      Print(P);
    end if;
    exit when Count = 1000000;
    Go_To_Next(P, Done);
    Count := Count + 1;
  end loop;
  
end Euler24;