import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.util.stream.Collectors;


public class ComputerScienceDegree {
    Set<Student> StudentList = new TreeSet<Student>();

    ComputerScienceDegree() {
        StudentList = new TreeSet<Student>();
    }

    void addStudent(Student s) {
        StudentList.add(s);
    }

    void load(String filename) throws IOException {
        try {
            BufferedReader in = new BufferedReader(new FileReader(filename));
            String line;

            while ((line = in.readLine()) != null) {
                List<String> Tok = Arrays.asList(line.split(","));

                Student newStudent = new Student(Tok.get(1), Integer.parseInt(Tok.get(0)));
                for (int i = 2; i < Tok.size(); i = i + 4) {
                    AbstractExam NewExam;

                    List<String> WritenGrade = Arrays.asList(Tok.get(i + 3).split(";"));
                    if (WritenGrade.size() > 1) {
                        NewExam = new ContinuousEvaluationExam(Tok.get(i), Integer.parseInt(Tok.get(i + 1)));
                        for (String WGstr : WritenGrade)
                            ((ContinuousEvaluationExam) NewExam)
                                    .addContinuousEvaluationGrade(Integer.parseInt(WGstr));
                    } else {
                        NewExam = new WrittenAndOralExam(Tok.get(i), Integer.parseInt(Tok.get(i + 1)));
                        ((WrittenAndOralExam) NewExam).setWrittenGrade(Integer.parseInt(WritenGrade.get(0).trim()));
                    }
                    NewExam.setOralGrade(Integer.parseInt(Tok.get(i + 2)));
                    newStudent.addExam(NewExam);
                }

                addStudent(newStudent);
            }
            in.close();
        } catch (Exception e) {
            throw new IOException(e.getMessage());
        }
    }

    int getYearlyStudents(int year) {
        //ExceptionHelper.CheckBound(year, 1, 3, "l'anno");
        if (year < 1 || year > 3)
        throw new IllegalArgumentException(
                String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]","l anno", year,1,3));

        return StudentList.stream().filter(x -> x.getYear() == year).collect(Collectors.toList()).size();
    }

    Student getTopStudentPerYear(int year) {
        //ExceptionHelper.CheckBound(year, 1, 3, "l'anno");

        if (year < 1 || year > 3)
        throw new IllegalArgumentException(
                String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]","l anno", year,1,3));


        ((Student) (StudentList.toArray()[3])).getYear();
        TreeSet<Student> EyarlyStudent = StudentList.stream().filter((x) -> x.getYear() == year)
                .collect(Collectors.toCollection(TreeSet::new));

        if (EyarlyStudent.size() == 0)
            return null;

        Student s = EyarlyStudent.last();
        List<Student> sl = new ArrayList<Student>();

        sl.add(s);

        for (int i = EyarlyStudent.size() - 1; i > 0; i--) {
            Student e = (Student) ((EyarlyStudent.toArray())[i]);
            if (s.getECTSAverage() != e.getECTSAverage())
                break;
            sl.add(e);
        }
        return sl.stream().max(Comparator.comparing(Student::getStudentNumber)).get();
    }

}
