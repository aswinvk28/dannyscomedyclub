<?php 

class DannysComedyClubPaginator {
    private $vars;
    
    public function __construct($vars) {
        $this->vars = $vars;
    }
    
    public function render_variables() {
        $this->vars['prev'] = $this->vars['next'] = '#';
        if(( $this->vars['page'] * $this->vars['length'] ) < $this->vars['count']) {
            $this->vars['li_next'] = 'active bootstrap_title';
            $this->vars['next'] = '#/!/page/' . ($this->vars['page'] + 1);
        } else {
            $this->vars['li_next'] = 'disabled';
        }
        if(( ($this->vars['page'] - 1) * $this->vars['length'] > 0 ) ) {
            $this->vars['li_prev'] = 'active bootstrap_title';
            $this->vars['prev'] = '#/!/page/' . ($this->vars['page'] - 1);
        } else {
            $this->vars['li_prev'] = 'disabled';
        }
    }
    
    public function getVars() {
        return $this->vars;
    }
}

?>