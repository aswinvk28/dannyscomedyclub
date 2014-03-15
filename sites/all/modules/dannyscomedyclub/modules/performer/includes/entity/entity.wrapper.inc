<?php

class PerformerEntityWrapper {
    public static function data($values) {
        return array(
            'performer_email' => !empty($values['performer_email']) ? $values['performer_email'] : NULL,
            'performer_fb' => !empty($values['performer_fb']) ? $values['performer_fb'] : NULL,
            'performer_twitter' => !empty($values['performer_twitter']) ? $values['performer_twitter'] : NULL,
            'performer_yt' => !empty($values['performer_yt']) ? $values['performer_yt'] : NULL,
            'performer_website' => !empty($values['performer_website']) ? $values['performer_website'] : NULL,
            'performer_opt' => NULL
        );
    }
}

?>