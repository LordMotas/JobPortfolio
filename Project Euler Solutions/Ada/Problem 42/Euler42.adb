--Project Euler #42
--Triangle number formula is (1/2)*N(N+1)
--SKY is 19 + 11 + 25 = 55 = t10, a triangle word
--How many words in the file are triangle words?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;

procedure Euler42 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  Answer : Integer := 0;
  Input_File : File_Type;
  Word : SU.Unbounded_String := SU.To_Unbounded_String("");
  type IntegerArray is array(1..100) of Integer;
  IntArray : IntegerArray;
  Sum : Integer := 0;
  StartString : Boolean := False;
  
begin

  --Create the triangle array of stuff
  for I in 1..100 loop
    IntArray(I) := Integer((1.0/2.0)*(Float(I))*(Float(I)+1.0));
  end loop;

  IO.Open(File => Input_File, Mode => IO.In_File, Name => "problem-42-data.txt");

  declare
    AllWords : SU.Unbounded_String := Get_Line(Input_File);
  begin
    For I in 1..Length(AllWords) loop
      if Element(AllWords, I) = '"' then
        if StartString = True then
          --End of a word
          For I in 1..Length(Word) loop
            Sum := Sum + Character'Pos(SU.To_String(Word)(I))-64;
          end loop;
          For J in 1..IntArray'Length loop
            if Sum = IntArray(J) then
              Answer := Answer + 1;
            end if;
          end loop;
          Sum := 0;
          Word := SU.To_Unbounded_String("");
          StartString := False;
        else
          --Beginning of a word
          StartString := True;
        end if;
      elsif Element(AllWords, I) /= ',' then
        Append(Word, SU.To_Unbounded_String(SU.To_String(AllWords)(I..I)));
      end if;
    end loop;
  end;

  <<endProgram>>

  IO.Close(File => Input_File);

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler42;