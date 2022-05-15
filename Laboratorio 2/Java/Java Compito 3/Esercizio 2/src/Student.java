public class Student implements Comparable<Student> {
    private String nome;
    private int studentNumber;
    private ListExam ListExam = new ListExam();

    Student(String _nome, int _studentNumber) {
        nome = _nome;
        studentNumber = _studentNumber;
    }

    public String getName() {
        return nome;
    }

    public int getStudentNumber() {
        return studentNumber;
    }

    void addExam(AbstractExam exam) {
        ListExam.add(exam);
    }

    int getYear() {
        int CfuObtainde = ListExam.CalcolaCFU();
        if (CfuObtainde >= 120)
            return 3;
        if (CfuObtainde >= 60)
            return 2;
        return 1;
    }

    public double getECTSAverage() {
        return ListExam.MediaECTS();
    }


    @Override
    public int compareTo(Student stu) {

        double ECTSA1 = getECTSAverage(), ECTSA2 = stu.getECTSAverage();

        if (ECTSA1 == ECTSA2)
            return 0;

        return ECTSA1 > ECTSA2 ? 1 : -1;
    }
}
