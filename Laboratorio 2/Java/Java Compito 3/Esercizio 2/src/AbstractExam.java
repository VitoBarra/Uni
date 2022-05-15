
public abstract class AbstractExam implements IExem {
    protected int CFU;
    protected String examName;
    protected int oralGrade;

    public AbstractExam(String _examName, int _cfu) {
        if (_examName != null && !_examName.trim().isEmpty())
            examName = _examName;
        CFU = _cfu;
    }

    public int getCFU() {
        return CFU;
    }

    public String getExamName() {
        return examName;
    }

    public int getOralGrade() {
        return oralGrade;
    }

    public void setOralGrade(int _oralGrade) {
        // ExceptionHelper.CheckBound(_writtenGrade,0,30,"il voto");
        if (_oralGrade < 0 || _oralGrade > 30)
            throw new IllegalArgumentException(
                    String.format("%s %s non è valido, per essere valido deve essere nel intervallo [%s,%s]", "il voto",
                            _oralGrade, 0, 30));
        oralGrade = _oralGrade;
    }

}
