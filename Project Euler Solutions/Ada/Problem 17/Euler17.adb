--Project Euler #17
--If the numbers 1 to 5 are written out in words:
--one, two, three, four, five, then there are 19 letters used in total.
--If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words,
--how many latters would be used?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;

procedure Euler17 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable declarations
  answer : Integer := 0;
  Ones : array(0..8) of SU.Unbounded_String := (SU.To_Unbounded_String("one"),SU.To_Unbounded_String("two"),SU.To_Unbounded_String("three"),SU.To_Unbounded_String("four"),SU.To_Unbounded_String("five"),SU.To_Unbounded_String("six"),SU.To_Unbounded_String("seven"),SU.To_Unbounded_String("eight"),SU.To_Unbounded_String("nine"));
  Teens : array(0..8) of SU.Unbounded_String := (SU.To_Unbounded_String("eleven"),SU.To_Unbounded_String("twelve"),SU.To_Unbounded_String("thirteen"),SU.To_Unbounded_String("fourteen"),SU.To_Unbounded_String("fiveteen"),SU.To_Unbounded_String("sixteen"),SU.To_Unbounded_String("seventeen"),SU.To_Unbounded_String("eighteen"),SU.To_Unbounded_String("nineteen"));
  Tens : array(0..9) of SU.Unbounded_String := (SU.To_Unbounded_String(""),SU.To_Unbounded_String("ten"),SU.To_Unbounded_String("twenty"),SU.To_Unbounded_String("thirty"),SU.To_Unbounded_String("forty"),SU.To_Unbounded_String("fifty"),SU.To_Unbounded_String("sixty"),SU.To_Unbounded_String("seventy"),SU.To_Unbounded_String("eighty"),SU.To_Unbounded_String("ninety"));
  Hundreds : array(0..9) of SU.Unbounded_String := (SU.To_Unbounded_String(""),SU.To_Unbounded_String("onehundred"),SU.To_Unbounded_String("twohundred"),SU.To_Unbounded_String("threehundred"),SU.To_Unbounded_String("fourhundred"),SU.To_Unbounded_String("fivehundred"),SU.To_Unbounded_String("sixhundred"),SU.To_Unbounded_String("sevenhundred"),SU.To_Unbounded_String("eighthundred"),SU.To_Unbounded_String("ninehundred"));
  Final : SU.Unbounded_String := SU.To_Unbounded_String("");
  
begin

  for K in 0..Hundreds'Length - 1 loop
    for J in 0..Tens'Length - 1 loop
      if K > 0 then
        --IO.Put(SU.To_String(Hundreds(K)));
        Final := Final & Hundreds (K);
        if J >= 1 then
          --IO.Put("and "&SU.To_String(Tens(J)));
          --IO.New_Line;
          Final := Final & SU.TO_Unbounded_String("and") & Tens (J);
        --else
          --IO.Put_Line("");
        end if;
      else
        if J > 0 then
          --IO.Put(SU.To_String(Tens(J)));
          --IO.New_Line;
          Final := Final & Tens (J);
        end if;
      end if;
      for I in 0..Ones'Length - 1 loop
        if K > 0 then
          --IO.Put(SU.To_String(Hundreds(K)&" and "));
          Final := Final & Hundreds (K) & SU.To_Unbounded_String("and");
        end if;
        if J = 1 then
          --IO.Put_Line(SU.To_String(Teens(I)));
          Final := Final & Teens (I);
        else
          if J > 0 then
            --IO.Put(SU.To_String(Tens(J))&" ");
            Final := Final & Tens (J);
          end if;
          --IO.Put_Line(SU.To_String(Ones(I)));
          Final := Final & Ones (I);
        end if;
      end loop;
    end loop;
  end loop;
  
  Final := Final & SU.To_unbounded_String("onethousand");
  
  IO.Put_Line("The answer is: "&Integer'Image(Length(Final)));
  
end Euler17;