--Project Euler #44
--Pentagonal numbers are Pn=n(3n-1)/2
--Find the pair of pentagonal numbers Pj and Pk for which their sum and difference
--are pentagonal and D=|Pk-Pj| is minimized. What is the value of D?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use ada.Strings.Unbounded.Text_IO;

procedure Euler44 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  Sum, Diff : Integer := 0;
  Answer : Integer := Integer'Last;
  IntArray : array(1..3000) of Positive;
  SumExists, DiffExists : Boolean := False;

begin

  --Generate Pentagonal numbers
  For N in 1..3000 loop
    IntArray(N) := (N*((3*N)-1))/2;
  end loop;
  For J in 1000..2200 loop
    For K in 1000..2200 loop
      SumExists := False;
      DiffExists := False;
      Sum := IntArray(J) + IntArray(K);
      Diff := Abs(IntArray(J) - IntArray(K));
      For I in 1..3000 loop
        if IntArray(I) = Sum then
          SumExists := True;
        end if;
        if IntArray(I) = Diff then
          DiffExists := True;
        end if;
      end loop;
      if SumExists and then DiffExists then
        if Answer > Diff then
          Answer := Diff;
        end if;
      end if;
    end loop;
  end loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer));

end Euler44;