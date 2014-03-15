<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"
  <?php print $rdf_namespaces; ?>>

<head profile="<?php print $grddl_profile; ?>">
  <?php print $head; ?>
  <title>
      <?php print $head_title_array['title'] . $head_title_array['tags'] . $head_title_array['page'] . ' - ' . $head_title_array['name']; ?>
  </title>
  <?php print $styles; ?>
  <meta http-equiv="content-language" content="en-gb">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
<!--[if lte IE 8]>
    <script src="<?php echo base_path(). path_to_theme(); ?>/js/html5.js" type="text/javascript"></script>
    <script src="/sites/default/packages/PIE/PIE.js" type="text/javascript"></script>
<![endif]-->
</head>
<body class="<?php print $classes; ?>" <?php print $attributes; ?>>
    <div class="absolute-image page_wrapper hidden-phone"></div>
    <div class="absolute-image page_container hidden-phone"></div>
    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
    <?php print $scripts; ?>
    <?php // if ($md_minimal_analytics) print $md_minimal_analytics; ?>
</body>
</html>
