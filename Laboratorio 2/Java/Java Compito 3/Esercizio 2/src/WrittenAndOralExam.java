
public class WrittenAndOralExam extends AbstractExam {

    protected int writtenGrade;

    public WrittenAndOralExam(String _examName, int _cfu) {
        super(_examName, _cfu);
        oralGrade = 0;
    }

    @Override
    public int getGrade() {
        return Math.round((float)(oralGrade + writtenGrade) / 2);
    }

    public int getWrittenGrade() {
        return writtenGrade;
    }

    public void setWrittenGrade(int _writtenGrade) {
        if (_writtenGrade < 0 || _writtenGrade > 30)
        throw new IllegalArgumentException(
                String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]","il voto", _writtenGrade,0,30));
            writtenGrade = _writtenGrade;
    }

}
