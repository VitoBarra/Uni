import java.util.*;

public class ContinuousEvaluationExam extends AbstractExam{

   List<Integer> continuousEvaluationGrades;

    public ContinuousEvaluationExam(String _examName, int _cfu) {
        super(_examName, _cfu);
        continuousEvaluationGrades = new ArrayList<Integer>();
    }

    @Override
    public int getGrade() {
         int n = continuousEvaluationGrades.stream().reduce(0,(sub,e)-> sub+e);
         float WritenContinuousGrade= Math.round((float)(n)/continuousEvaluationGrades.size());
         return  Math.round((float)(WritenContinuousGrade+oralGrade)/2);
    }



    public void addContinuousEvaluationGrade(int g)
    {
        //ExceptionHelper.CheckBound(g, 0, 30, "il voto");
        if (g < 0 || g > 30)
        throw new IllegalArgumentException(
                String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]","il voto", g,0,30));
        continuousEvaluationGrades.add(g);
    }
    
}
