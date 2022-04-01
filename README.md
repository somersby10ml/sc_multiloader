
# StarCraft Multi-Loader
StarCraft Multi-Loader 

## Summary
StarCraft.exe has a handle like this:
```
Event, \Sessions\1\BaseNamedObjects\Starcraft Check For Other Instances, 0x00
```
Duplicate execution is possible by terminating this.

## Process
※ This requires administrator privileges.

1. Get system all handle list from `ZwQueryInformationProcess`
1. Copy handle from `DuplicateHandle`
1. Get handle name from `NtQueryObject`
1. check if name is `Starcraft Check For Other Instances`
1. Close handle `DuplicateHandle` flag `DUPLICATE_CLOSE_SOURCE`
