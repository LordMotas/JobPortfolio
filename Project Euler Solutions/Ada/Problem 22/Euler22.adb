--Project Euler #22
--Sort the names in the text file alphabetically
--Then find the 'score' for each name
--Then multiply that score by the position in the list
--What is the sum of all the final scores?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler22 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable declarations
  File : File_Type;
  Char : Character;
  Str : SU.Unbounded_String;
  StartString : Boolean := False;
  type StrArray is array(Positive range <>) of SU.Unbounded_String;
  StringArray : StrArray := (1 .. 5163 => (SU.To_Unbounded_String("")));
  Count : Integer := 1;
  Temp : SU.Unbounded_String;
  J : Integer := 1;
  Answer : Integer := 0;
  Next : Integer := 0;

begin

  IO.Open(File => File, Mode => IO.In_File, Name => "names.txt");

while not IO.End_Of_Line (File) loop
  IO.Get(file => File, Item => Char);
  if Char = '"' and then StartString = False then
    StartString := True;
    Str := SU.To_Unbounded_String("");
  elsif Char = '"' and then StartString = True then
    StartString := False;
    --Put it in an array
    StringArray (Count) := Str;
    Count := Count + 1;
    if Str = SU.To_Unbounded_String("ALONSO") then
      exit;
    end if;
  end if;
  if StartString = True and then Char /= '"' then
    Str := Str & Char;
  end if;
end loop;

  --Sort the array
  for I in 1..StringArray'Length - 1 loop
    J := 1;
    while J /= StringArray'Length loop
      if StringArray(J) > StringArray(J+1) then
        Temp := StringArray(J);
        StringArray(J) := StringArray(J+1);
        StringArray(J+1) := Temp;
      end if;
      J := J + 1;
    end loop;
  end loop;
  
  --Calculate the name scores
  for I in StringArray'Range loop
    for J in 1..Length(StringArray(I)) loop
      --This converts each letter to a score
      Next := (Next + Integer(Character'Pos(Element(StringArray(I), J)) - 64));
    end loop;
    Next := Next * I;
    Answer := Answer + Next;
    Next := 0;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));
  
end Euler22;