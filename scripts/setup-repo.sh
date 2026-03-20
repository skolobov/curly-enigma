#!/usr/bin/env bash
set -euo pipefail

# Repository setup script
# Configures branch protection, labels, and repository settings
# using the GitHub CLI (gh). Idempotent — safe to run multiple times.

REPO="${REPO:-skolobov/curly-enigma}"

echo "==> Configuring repository settings for ${REPO}"

# --- Repository settings ---

echo "--> Disabling merge commits, enabling squash and rebase merge"
gh api -X PATCH "repos/${REPO}" \
  -f allow_merge_commit=false \
  -f allow_squash_merge=true \
  -f allow_rebase_merge=true \
  -f delete_branch_on_merge=true \
  --silent

# --- Labels ---

echo "--> Creating labels (skipping if they already exist)"
gh label create verify \
  --repo "${REPO}" \
  --description "Triggers integration/E2E tests" \
  --color "0E8A16" 2>/dev/null || true

gh label create publish \
  --repo "${REPO}" \
  --description "Triggers RC package build and upload" \
  --color "D93F0B" 2>/dev/null || true

# --- Branch protection for main ---

echo "--> Configuring branch protection for main"

# Get the required status check contexts from our workflows
gh api -X PUT "repos/${REPO}/branches/main/protection" \
  --input - <<'JSON'
{
  "required_status_checks": {
    "strict": true,
    "contexts": [
      "MegaLinter",
      "C++ Lint",
      "ubuntu-latest",
      "macos-latest",
      "windows-latest"
    ]
  },
  "enforce_admins": false,
  "required_pull_request_reviews": {
    "required_approving_review_count": 0
  },
  "required_linear_history": true,
  "restrictions": null
}
JSON

echo "==> Repository setup complete"
echo ""
echo "Branch protection rules for main:"
echo "  - Require status checks to pass (lint + build matrix)"
echo "  - Require branches to be up to date before merging"
echo "  - Enforce linear history (no merge commits)"
echo "  - Auto-delete head branches after merge"
echo "  - Merge commits disabled (squash and rebase only)"
