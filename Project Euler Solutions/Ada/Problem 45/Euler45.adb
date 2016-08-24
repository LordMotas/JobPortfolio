--Project Euler #45
--T->N(N+1)/2
--P->N(3N-1)/2
--H->N(2N-1)
--40755 is Triangle, Pentagonal, Hexagonal
--Find the next triangle number that is also pentagonal and hexagonal

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use ada.Strings.Unbounded.Text_IO;

procedure Euler45 is

  package IO renames Ada.Text_IO;
  package SU renames Ada.Strings.Unbounded;

  --Variable Declarations
  Answer : Long_Long_Integer := 0;
  TriArray : array(1..55385) of Long_Long_Integer;
  PenArray : array(1..31977) of Long_Long_Integer;
  HexArray : array(1..27693) of Long_Long_Integer;
  InPen, InHex : Boolean := False;

begin

  --Generate Triangle, Pentagonal, and Hexagonal Numbers
  for N in 1..55385 loop
    TriArray(N) := (Long_Long_Integer(N)*(Long_Long_Integer(N)+1))/2;
  end loop;
  for N in 1..31977 loop
    PenArray(N) := (Long_Long_Integer(N)*((3*Long_Long_Integer(N))-1))/2;
  end loop;
  for N in 1..27693 loop
    HexArray(N) := Long_Long_Integer(N)*((2*Long_Long_Integer(N))-1);
  end loop;

  for I in reverse 286..55385 loop
    InPen := False;
    InHex := False;
    for J in reverse 1..31977 loop
      if TriArray(I) = PenArray(J) then
        InPen := True;
      end if;
    end loop;
    for J in reverse 1..27693 loop
      if TriArray(I) = HexArray(J) then
        InHex := True;
      end if;
    end loop;
    if InPen and then InHex then
      Answer := Long_Long_Integer(TriArray(I));
      goto endProgram;
    end if;
  end loop;

  <<endProgram>>

  IO.Put_Line("The answer is: "&Long_Long_Integer'Image(Answer));

end Euler45;