public class Main {
    public static void main(String[] args) throws Exception {
        ComputerScienceDegree CSD = new ComputerScienceDegree();
        AbstractExam a = new WrittenAndOralExam("ad", 4);
        try {
            a.setOralGrade(31);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            a.setOralGrade(-1);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        CSD.load("students.csv");

        for (int i = -1; i < 4; i++) {
            try {
                Student s = CSD.getTopStudentPerYear(i);
                int n = CSD.getYearlyStudents(i);
                System.out.println(s);
                System.out.println(n);
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }

        ContinuousEvaluationExam b = new ContinuousEvaluationExam("Analisi", 12);
        b.setOralGrade(30);
        try {

            b.addContinuousEvaluationGrade(0);
            b.addContinuousEvaluationGrade(30);
            b.addContinuousEvaluationGrade(31);
            b.addContinuousEvaluationGrade(-1);
            b.getGrade();
            b.addContinuousEvaluationGrade(35);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

    }
}
