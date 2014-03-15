<?php

class DannysComedyClubDotCom {

    private static $archivedShows = array();
    
    private static $promotedShows = array();
    
    private static $activeInstance = null;
    
    public static $promotedPerformances = array();
    
    private static $intro_articles = array();
    
    static function getActiveInstance() {
        if(!isset(self::$activeInstance)) {
            self::$activeInstance = dannyscomedyclub_memory_queue()->claimItem(30, 'dannyscomedyclub')->data;
        }
        return self::$activeInstance;
    }

    static function filterShows($item) {
        return $item['#bundle'] == 'shows';
    }
    
    static function getCurrentAndNextYear() {
        $year_after = ((int) date('Y')) - 1;
        $date_after = new DateTime();
        $date_after->setDate($year_after, 1, 1);
        $date_after->setTime(0, 0, 0);

        $year_int = $year_after + 1;
        $date_int = new DateTime();
        $date_int->setDate($year_int, 1, 1);
        $date_int->setTime(0, 0, 0);

        $year_before = $year_after + 2;
        $date_before = new DateTime();
        $date_before->setDate($year_before, 1, 1);
        $date_before->setTime(0, 0, 0);
        return array(
            'after' => $date_after->format('Y-m-d H:m:s'),
            'before' => $date_before->format('Y-m-d H:m:s'),
            'interval' => $date_int->format('Y-m-d H:m:s')
        );
    }
    
    static function getArtistesCount() {
        $count_query = db_select('node', 'n')->fields('n', array('nid', 'title'))->orderBy('n.changed', 'DESC')->condition("n.status", 1)->condition("n.type", 'artistes');
        $count = $count_query->countQuery()->execute()->fetchField();
        return $count;
    }

    static function getArticles(&$vars) {
        $articles = array();
        if(isset($vars['page']['content']['system_main']['nodes'])) {
            $articles = array_filter($vars['page']['content']['system_main']['nodes'], array('self', 'filterArticles'));
            $vars['page']['content']['system_main']['nodes'] = array_diff_key($vars['page']['content']['system_main']['nodes'], $articles);
            uasort($articles, array('self', 'sortArticles'));
        }
        return $articles;
    }
    
    static function setIntroArticles(&$articles) {
        if(empty(self::$intro_articles)) {
            self::$intro_articles = array_filter($articles, array('self', 'filterIntroArticles'));
            $articles = array_diff_key($articles, self::$intro_articles);
        }
    }
    
    static function getIntroArticles() {
        return self::$intro_articles;
    }
    
    static function filterArticles($item) {
        return $item['#bundle'] == 'article';
    }
    
    static function filterIntroArticles($item) {
        $field_items = field_get_items('node', $item['#node'], 'field_boolean');
        return $field_items[0]['value'] == '1';
    }
    
    static function sortArticles($value1, $value2) {
        $item1 = field_get_items('node', $value1['#node'], 'field_boolean');
        $item2 = field_get_items('node', $value2['#node'], 'field_boolean');
        if ($item1[0]['value'] == $item2[0]['value']) { return 0; }
        return ($item1[0]['value'] > $item2[0]['value']) ? -1 : 1;
    }
}

?>