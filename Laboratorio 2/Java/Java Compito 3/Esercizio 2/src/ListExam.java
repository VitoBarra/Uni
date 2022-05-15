import java.util.*;

public class ListExam extends ArrayList<AbstractExam> {

    @Override
    public boolean add(AbstractExam e) {
        String examName = e.getExamName();

        for (AbstractExam ele : this)
            if (examName.equals(ele.getExamName())) {
                this.remove(e);
                break;
            }

        return super.add(e);
    }

    public int CalcolaCFU() {
        int totaleCFU = 0;
        for (AbstractExam e : this)
            if (e.getGrade() > 17)
                totaleCFU += e.getCFU();

        return totaleCFU;
    }

    public double MediaECTS() {
        if(this.size()==0) return 0;
        
        double totCFU = 0;
        double totGradeValue = 0;
        for (AbstractExam e : this)
            if (e.getGrade() > 17) {
                totCFU += e.getCFU();
                totGradeValue += e.getGrade()*e.getCFU();
            }
            
        return totGradeValue/totCFU;
    }

}