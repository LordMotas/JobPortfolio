--Project Euler #26
--Find the value of d < 1000 for which 1/d contains
--the longest recurring cycle in its decimal fraction part.

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler26 is

  package IO renames Ada.Text_IO;
  
  --Variable Declarations
  Answer : Integer := 0;
  SequenceLength : Integer := 0;
  
begin
  First_Loop:
  for I in 1..1000 loop
    if SequenceLength >= I then
      exit First_Loop;
    end if;
    declare
      type IntArray is array (Natural range 0..999) of Integer;
      FoundRemainders : IntArray := (0 => 0, others => 0);
      Value : Integer := 1;
      Position : Integer := 0;
    begin
      while FoundRemainders(Value) = 0 and then Value /= 0 loop
        FoundRemainders(Value) := Position;
        Value := Value * 10;
        Value := Value mod I;
        Position := Position + 1;
      end loop;
      if Position - FoundRemainders(Value) > SequenceLength then
        SequenceLength := Position - FoundRemainders(Value);
        Answer := I;
      end if;
    end;
  end loop First_Loop;

  IO.Put_Line("The answer is: "&Integer'Image(Answer)&" with sequence length: "&Integer'Image(SequenceLength));
  
end Euler26;