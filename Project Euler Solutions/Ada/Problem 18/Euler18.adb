--Project Euler #18
--Find the path that returns the largest sum in the triangle

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler18 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  MAX_SIZE : Integer := 15;
  ARRAY_BOUND : Integer := MAX_SIZE - 1;
  Input_File : File_Type;
  subtype File_Bound is Integer range 0..MAX_SIZE; 
  Size : File_Bound := 1;
  I : File_Bound := 1;
  type IntArray is array(1..MAX_SIZE, 1..MAX_SIZE) of Integer;
  type StrArray is array(1..MAX_SIZE, 1..MAX_SIZE) of String(1..2);
  Rows : StrArray;
  IntRows : IntArray;
  Max : Integer;
  Answer : Integer := 0;
  Boundary : Integer := 1;
  
begin
  
  IO.Open(File => Input_File, Mode => IO.In_File, Name => "problem-18-data.txt");
  
  While_Loop:
  while not End_Of_File (Input_File) loop
    IO.Get(Input_File, Rows (Size, I));
    --IO.Put(Rows (Size, I)&" ");

    if I = Size then
      I := 0;
      exit when Size = MAX_SIZE;
      Size := Size + 1;
    end if;
    I := I + 1;
  end loop While_Loop;
  
  IO.Close(File => Input_File);
  
  --Convert from StrArray to IntArray
  for I in 1..MAX_SIZE loop
    for J in 1..Boundary loop
      IntRows(I, J) := Integer'Value(Rows(I, J));
    end loop;
    Boundary := Boundary + 1;
  end loop;
  
  for I in reverse 1..ARRAY_BOUND loop
    for J in 1..I loop
      if IntRows(I+1, J) > IntRows(I+1, J+1) then
        Max := IntRows(I+1, J);
      else
        Max := IntRows(I+1, J+1);
      end if;
      IntRows(I, J) := IntRows(I, J) + Max;
      if IntRows(I, J) > Answer then
        Answer := IntRows(I, J);
      end if;
    end loop;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler18;