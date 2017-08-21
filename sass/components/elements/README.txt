This directory is reserved for styling HTML elements.

We use one file per element.

This means styling for h1, h2, h3 ... h6 is available in the _h.scss file.

These files set very high level styling for their elements and may be overridden
in other files further down the cascade.

In Drupal, it's not uncommon to have
different h2 styling, for example, on a views block than the h2 that might be
found in the node body. The styling for that views block will be found in the
blocks directory or in the views directory. We haven't formalised on an
agreement yet - I'd prefer to keep it in the views directory (Mark C).
